#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int g_min = 199;
int min_h = 67, min_s = 67, min_v = 55, max_h = 153, max_s = 188, max_v = 255;
Mat src, mid, dst, dst_dilate, dst_canny;

static void my_threshold(int,void*);

static void find_circle(int, void*);

static void Trackbar(int, void*);

int main()
{
    string img_path = "/home/wsk/codes/cv_learning/ball.jpg";
    VideoCapture capture;
    capture.open(0);
    if(capture.isOpened())
    {
        cout<<"capture is opened"<<endl;
        while(1)
        {
            //src = imread(img_path);
            //blur(src, mid, Size(5,5));
            capture >> src;
            if(src.empty())   break;
            imshow("src", src);
            medianBlur(src, mid, 7);
            imshow("blur", mid);
            cvtColor(mid, mid, COLOR_BGR2HSV);
            inRange(mid, Scalar(min_h, min_s, min_v), Scalar(max_h, max_s, max_v), dst);
            namedWindow("binary", 1);
            // createTrackbar("min_h", "binary", &min_h, 255, Trackbar);
            // createTrackbar("min_s", "binary", &min_s, 255, Trackbar);
            // createTrackbar("min_v", "binary", &min_v, 255, Trackbar);
            // createTrackbar("max_h", "binary", &max_h, 255, Trackbar);
            // createTrackbar("max_s", "binary", &max_s, 255, Trackbar);
            // createTrackbar("max_v", "binary", &max_v, 255, Trackbar);
            imshow("binary", dst);
    
    
            find_circle(0, 0);
            // namedWindow("binary", 1);
            // createTrackbar("min :", "binary", &g_min, 255, my_threshold);
            // threshold(mid, dst, g_min, 255, THRESH_BINARY);
            // imshow("binary", dst);
            // find_circle(0,0);

            if(waitKey(5) >= 0)
                break;
        }
    }
    return 0;
}

static void my_threshold(int, void*)
{
    Mat img_src = mid.clone();
    Mat img_dst;
    threshold(mid, dst, g_min, 255, THRESH_BINARY);
    imshow("binary", dst);
    find_circle(0,0);
}

static void find_circle(int, void*)
{
    int n_StructElementSize = 15;
    Mat element = getStructuringElement(MORPH_RECT, Size(2*n_StructElementSize+1, 2*n_StructElementSize+1), Point(n_StructElementSize, n_StructElementSize));
    morphologyEx(dst, dst_dilate, MORPH_CLOSE, element);
    imshow("dilate", dst_dilate);
    Canny(dst_dilate, dst_canny, 3, 9, 3);
    imshow("canny", dst_canny);
    vector<Vec3f> circles;
    Mat src_circle = src.clone();
    HoughCircles(dst_canny, circles, HOUGH_GRADIENT, 1.5, 100, 200, 35, 0, 100);
    for (size_t i = 0; i < circles.size(); i++)
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = circles[i][2];
        cout<<"R = "<<radius<<endl;
        circle(src_circle, center, 3, Scalar(0,255,0), -1);
        circle(src_circle, center, radius, Scalar(0,0,255), 3);
    }
    imshow("result", src_circle);
}

static void Trackbar(int, void*)
{
    inRange(mid, Scalar(min_h, min_s, min_v), Scalar(max_h, max_s, max_v), dst);
    imshow("binary", dst);
    find_circle(0, 0);
}