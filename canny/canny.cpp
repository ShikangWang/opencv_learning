#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("/home/wsk/codes/cv_learning/read_img/test.jpg");
    imshow("src", img);
    Mat img_canny;
    cvtColor(img, img_canny, COLOR_BGR2GRAY);
    imshow("gray", img_canny);
    blur(img_canny, img_canny, Size(3,3));
    imshow("blur", img_canny);
    Canny(img_canny, img_canny, 45, 51, 3);
    imshow("canny", img_canny);

    waitKey(0);
    return 0;
}