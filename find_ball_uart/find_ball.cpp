#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>


using namespace std;
using namespace cv;

#define USE_CAPTURE 0
#define IS_RASPI    0
#define IS_DEBUG    0

#if IS_RASPI
#include <wiringpi.h>
#include <wiringSerial.h>
#endif

int g_min = 199;
int min_h = 67, min_s = 52, min_v = 55, max_h = 153, max_s = 188, max_v = 255;
Mat src, mid, dst, dst_dilate, dst_canny;

static void my_threshold(int,void*);

static void find_circle(int, void*);

static void Trackbar(int, void*);

int main()
{
    #if IS_RASPI
    wiringPiSetup();
    int fd = serialOpen("/dev/ttyAMA1", 9600);
    #endif
    string img_path = "../../ball.jpg";
    #if USE_CAPTURE
    VideoCapture capture;
    capture.open(0);
    if(capture.isOpened())
    #endif
    {
        cout<<"capture is opened"<<endl;
        while(1)
        {
            #if USE_CAPTURE
            capture >> src;
            #else
            src = imread(img_path);
            #endif
            //blur(src, mid, Size(5,5));
            if(src.empty())   break;
            //imshow("src", src);
            medianBlur(src, mid, 7);
            //imshow("blur", mid);
            cvtColor(mid, mid, COLOR_BGR2HSV);
            inRange(mid, Scalar(min_h, min_s, min_v), Scalar(max_h, max_s, max_v), dst);
            namedWindow("binary", 1);
            #if IS_DEBUG
            createTrackbar("min_h", "binary", &min_h, 255, Trackbar);
            createTrackbar("min_s", "binary", &min_s, 255, Trackbar);
            createTrackbar("min_v", "binary", &min_v, 255, Trackbar);
            createTrackbar("max_h", "binary", &max_h, 255, Trackbar);
            createTrackbar("max_s", "binary", &max_s, 255, Trackbar);
            createTrackbar("max_v", "binary", &max_v, 255, Trackbar);
            #endif
            imshow("binary", dst);
    
    
            find_circle(0, 0);
            // namedWindow("binary", 1);
            // createTrackbar("min :", "binary", &g_min, 255, my_threshold);
            // threshold(mid, dst, g_min, 255, THRESH_BINARY);
            // imshow("binary", dst);
            // find_circle(0,0);

            if(waitKey(0) >= 0)
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
    HoughCircles(dst_canny, circles, HOUGH_GRADIENT, 1.5, 100, 200, 35, 150, 250);//change
    for (size_t i = 0; i < circles.size(); i++)
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = circles[i][2];
        cout<<"R = "<<radius<<endl;
        circle(src_circle, center, 3, Scalar(0,255,0), -1);
        circle(src_circle, center, radius, Scalar(0,0,255), 3);
        #if IS_RASPI
            serialPrintf(fd, "C=%d, %d", circles[i][0], circles[i][1]);
        #endif
    }
    imshow("result", src_circle);
}

static void Trackbar(int, void*)
{
    inRange(mid, Scalar(min_h, min_s, min_v), Scalar(max_h, max_s, max_v), dst);
    imshow("binary", dst);
    find_circle(0, 0);
}