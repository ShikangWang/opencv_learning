#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("/home/wsk/codes/cv_learning/read_img/test.jpg");
    Mat img_erode, img_dilate;
    Mat element = getStructuringElement(MORPH_RECT, Size(15,15));
    erode(img, img_erode, element);
    dilate(img, img_dilate, element);
    imshow("src", img);
    imshow("erode", img_erode);
    imshow("dilate", img_dilate);
    waitKey(0);
    return 0;
}