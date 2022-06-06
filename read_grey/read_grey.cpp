#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("/home/wsk/codes/cv_learning/read_img/test.jpg");

    Mat img_grey;
    cvtColor(img, img_grey, COLOR_BGR2GRAY);
    imshow("read_src", img);
    imshow("read_grey", img_grey);
    waitKey(0);
    return 0;
}
