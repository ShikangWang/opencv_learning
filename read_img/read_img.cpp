#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img_dst;

int main()
{
    Mat img = imread("../0.jpg");
    Mat cameraMatrix=Mat::eye(3,3,CV_64F);
    cameraMatrix.at <double>(0,0)=477.3549;
    cameraMatrix.at <double>(0,2)=323.2081;
    cameraMatrix.at <double>(1,1)=477.5523;
    cameraMatrix.at <double>(1,2)=231.8920;
    cameraMatrix.at <double>(2,2)=1;
    Mat distCoeffs=Mat::zeros(5,1,CV_64F);
    distCoeffs.at <double>(0,0)=-0.4188;
    distCoeffs.at <double>(0,1)=0.1903;

     imshow("src", img);
    undistort(img, img_dst, cameraMatrix, distCoeffs);
    imshow("result", img_dst);

    waitKey(0);
    return 0;
}
