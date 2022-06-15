#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>

#define IS_DEBUG 1

using namespace std;
using namespace cv;

Mat img_src, img_mid, img_binary, img_dst;
vector<vector<Point>> squares;
int h_min=5, h_max=255, s_min=54, s_max=255, v_min=47, v_max=255;
string img_path = "../rect.jpg";

static void binary_trackbar(int, void*);
vector<vector<Point>> find_rect(Mat binary);

int main()
{
    img_src = imread(img_path);
    imshow("src", img_src);

    //blur(img_src, img_mid, Size(7,7));
    medianBlur(img_src, img_mid, 3);

    cvtColor(img_mid, img_mid, COLOR_BGR2HSV);

    inRange(img_mid, Scalar(h_min, s_min, v_min), Scalar(h_max, s_max, v_max), img_binary);
    namedWindow("binary");
    #if IS_DEBUG
    createTrackbar("h_min", "binary", &h_min, 255, &binary_trackbar);
    createTrackbar("s_min", "binary", &s_min, 255, &binary_trackbar);
    createTrackbar("v_min", "binary", &v_min, 255, &binary_trackbar);
    createTrackbar("h_max", "binary", &h_max, 255, &binary_trackbar);
    createTrackbar("s_max", "binary", &s_max, 255, &binary_trackbar);
    createTrackbar("v_max", "binary", &v_max, 255, &binary_trackbar);
    #endif
    imshow("binary", img_binary);
    
    vector<vector<Point>> rect;
    rect = find_rect(img_binary);
    
    if(rect.size())
    {
        int row, col;
        row = img_src.rows;
        col = img_src.cols;
        
        Point2f dst_points[3] = {Point2f(0, 0), Point2f(0, row), Point2f(col, row)};
        Point2f src_points[3] = {rect[0][3], rect[0][0], rect[0][1]};
        Mat M2 = getAffineTransform(src_points, dst_points);
        cout<<"test"<<endl;
        Size size2(img_src.cols, img_src.rows);
        warpAffine(img_src, img_dst, M2, size2);
    }

    imshow("dst", img_dst);
    waitKey(0);

    return 0;
}


static void binary_trackbar(int, void*)
{
    inRange(img_mid, Scalar(h_min, s_min, v_min), Scalar(h_max, s_max, v_max), img_binary);
    imshow("binary", img_binary);
}

vector<vector<Point>> find_rect(Mat binary)
{
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