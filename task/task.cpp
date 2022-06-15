#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>

using namespace std;
using namespace cv;

Mat img_src, img_mid, img_binary, img_affine, img_dst;

vector<vector<Point>> find_rect(Mat binary);

Point2f src_point[3];


int main()
{
    VideoCapture capture;
    capture.open(0);
    if(capture.isOpened())
    {
        while(1)
        {
            cout<<"capture is opened"<<endl;
            capture >> img_src;
            if(img_src.empty())
                break;//error occured
            blur(img_src, img_mid, Size(7,7));
            cvtColor(img_mid, img_mid, COLOR_BGR2HSV);
            inRange(img_mid, Scalar(5,54,47), Scalar(255,255,255), img_binary);

            vector<vector<Point>> rect; //find_rect
            rect = find_rect(img_binary);
            if(rect.size() == 1)
            {
                src_point[0] = rect[0][0];
                src_point[1] = rect[0][1];
                src_point[2] = rect[0][2];
            }
            Point2f dst_point[3] = {Point2f(0,0), Point2f(0, img_src.rows), Point2f(img_src.cols, img_src.cols)};
            Mat M2 = getAffineTransform(src_point, dst_point);
            Size size2(img_src.cols, img_src.rows);
            warpAffine(img_src, img_affine, M2, size2);


            blur(img_affine, img_mid, Size(7,7));
            cvtColor(img_affine, img_mid, COLOR_BGR2HSV);
            inRange(img_mid,Scalar(), Scalar(), img_binary);
        }
    }
}

vector<vector<Point>> find_rect(Mat binary)
{
    vector<vector<Point>> squares;
    Mat img_edge, img_dst;
    img_dst = img_src.clone();
    Canny(binary, img_edge, 3, 9, 3);
    imshow("edge", img_edge);

    vector<vector<Point>>   contours;
    vector<Vec4i>    hierachy; 
    findContours(img_edge, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<Point> approx;
    for(size_t i=0; i < contours.size(); i++)
    {
        //cout<<contours[i]<<endl;
        approxPolyDP(contours[i], approx, 10, true);
        cout<<"size = "<<approx.size()<<endl;
        cout<<approx<<endl;
        // for(size_t i=0; i<approx.size(); i++)
        // {
        //     line(img_dst, approx[i], approx[(i+1)%approx.size()], Scalar(255,0,0));
        // }
        if((approx[0].x+approx[0].y)>(approx[3].x+approx[3].y))
        {
            Point temp = approx[3];
            approx[3] = approx[2];
            approx[2] = approx[1];
            approx[1] = approx[0];
            approx[0] = temp;
        }
        if(approx.size() == 4)
        {
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