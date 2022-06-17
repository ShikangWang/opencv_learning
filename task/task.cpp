#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>

using namespace std;
using namespace cv;

Mat img_src, img_mid, img_binary, img_affine, img_mid2, img_binary2, img_dst;

vector<vector<Point>> find_rect(Mat binary);

Point2f src_point[3];

vector<vector<Point>> squares;

int h_min1=5, h_max1=255, s_min1=54, s_max1=255, v_min1=47, v_max1=255, h_min2=0, h_max2=255, s_min2=0, s_max2=255, v_min2=0, v_max2=255;

double t=0;
float fps;

static void Broad_trackbar(int ,void*);
static void Ball_trackbar(int, void*);


int main()
{
    VideoCapture capture;
    capture.open(0);
    namedWindow("broad");
    createTrackbar("h_min", "broad", &h_min1, 255, &Broad_trackbar);
    createTrackbar("h_max", "broad", &h_max1, 255, &Broad_trackbar);
    createTrackbar("s_min", "broad", &s_min1, 255, &Broad_trackbar);
    createTrackbar("s_max", "broad", &s_max1, 255, &Broad_trackbar);
    createTrackbar("v_min", "broad", &v_min1, 255, &Broad_trackbar);
    createTrackbar("v_max", "broad", &v_max1, 255, &Broad_trackbar);

    namedWindow("ball");
    createTrackbar("h_min", "ball", &h_min2, 255, &Ball_trackbar);
    createTrackbar("h_max", "ball", &h_max2, 255, &Ball_trackbar);
    createTrackbar("s_min", "ball", &s_min2, 255, &Ball_trackbar);
    createTrackbar("s_max", "ball", &s_max2, 255, &Ball_trackbar);
    createTrackbar("v_min", "ball", &v_min2, 255, &Ball_trackbar);
    createTrackbar("v_max", "ball", &v_max2, 255, &Ball_trackbar);
    if(capture.isOpened())
    {
        cout<<"capture is opened"<<endl;
        while(1)
        {
            t = getTickCount();
            capture >> img_src;
            imshow("src", img_src);
            if(img_src.empty())
                break;//error occured
            blur(img_src, img_mid, Size(7,7));
            //medianBlur(img_src, img_mid, 3);
            cvtColor(img_mid, img_mid, COLOR_BGR2HSV);
            inRange(img_mid, Scalar(h_min1, s_min1, v_min1), Scalar(h_max1, s_max1, v_max1), img_binary);
            imshow("broad", img_binary);
            vector<vector<Point>> rect; //find_rect
            rect = find_rect(img_binary);
            if(rect.size() == 1)
            {
                src_point[0] = rect[0][0];
                src_point[1] = rect[0][1];
                src_point[2] = rect[0][2];
                Point2f dst_point[3] = {Point2f(0,0), Point2f(0, img_src.rows), Point2f(img_src.cols, img_src.cols)};
                Mat M2 = getAffineTransform(src_point, dst_point);
                Size size2(img_src.cols, img_src.rows);
                warpAffine(img_src, img_affine, M2, size2);
            }
            else
            {
                img_affine = img_src;
            }


            if(img_affine.empty())
            {
                cout<<"error"<<endl;
                break;
            }
            blur(img_affine, img_mid2, Size(7,7));
            cvtColor(img_affine, img_mid2, COLOR_BGR2HSV);
            inRange(img_mid2,Scalar(h_min2,s_min2, v_min2), Scalar(h_max2, s_max2, v_max2), img_binary2);
            imshow("ball", img_binary2);
            int n_StructElementSize = 15;
            Mat element = getStructuringElement(MORPH_RECT, Size(2*n_StructElementSize+1, 2*n_StructElementSize+1), Point(n_StructElementSize, n_StructElementSize));
            morphologyEx(img_binary2, img_mid2, MORPH_CLOSE, element);
            Canny(img_mid2, img_mid2, 3,9,3);
            vector<Vec3f> circles;
            HoughCircles(img_mid2, circles, HOUGH_GRADIENT, 1.5, 100, 200, 50, 5, 50);
            for(size_t i=0; i<circles.size(); i++)
            {
                Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                int radius = circles[i][2];
                circle(img_affine, center, 3, Scalar(0,0,255), -1);
                circle(img_affine, center, radius, Scalar(0,0,255), 3);
            }
            imshow("result", img_affine);


            t = (getTickCount()-t)/getTickFrequency();
            fps = 1.0/t;
            cout<<"FPS="<<fps<<endl;
            if(waitKey(5) >= 0)
                break;
        }
    }
}

vector<vector<Point>> find_rect(Mat binary)
{
    
    Mat img_edge, img_dst;
    img_dst = img_src.clone();
    Canny(binary, img_edge, 3, 9, 3);

    vector<vector<Point>>   contours;
    vector<Vec4i>    hierachy; 
    findContours(img_edge, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<Point> approx;
    for(size_t i=0; i < contours.size(); i++)
    {
        //cout<<contours[i]<<endl;
        approxPolyDP(contours[i], approx, 10, true);
        //cout<<"size = "<<approx.size()<<endl;
        //cout<<approx<<endl;
        // for(size_t i=0; i<approx.size(); i++)
        // {
        //     line(img_dst, approx[i], approx[(i+1)%approx.size()], Scalar(255,0,0));
        // }

        if(approx.size() == 4)
        {
            if((approx[0].x+approx[0].y)>(approx[3].x+approx[3].y))
            {
                Point temp = approx[3];
                approx[3] = approx[2];
                approx[2] = approx[1];
                approx[1] = approx[0];
                approx[0] = temp;
            }
            squares.push_back(approx);
        }
    }
    for(size_t i=0; i<squares.size(); i++)
    {
        for(int j=0; j<squares[i].size(); j++)
        {
            line(img_dst, squares[i][j], squares[i][(j+1)%squares[i].size()], Scalar(255,0,0));
        }
    }
    imshow("find_rect", img_dst);

    return squares;
}


static void Broad_trackbar(int, void*)
{
    if(!img_mid.empty())
    {
        inRange(img_mid, Scalar(h_min1, s_min1, v_min1), Scalar(h_max1, s_max1, v_max1), img_binary);
        imshow("broad", img_binary);
    }
}

static void Ball_trackbar(int, void*)
{
    if(!img_mid2.empty())
    {
        inRange(img_mid2,Scalar(h_min2,s_min2, v_min2), Scalar(h_max2, s_max2, v_max2), img_binary2);
        imshow("ball", img_binary2);
    }
}