#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat img = imread("/home/wsk/codes/cv_learning/read_img/test.jpg");
    imshow("src", img);
    Mat img_filter;
    blur(img, img_filter, Size(7,7));
    imshow("filter", img_filter);

    waitKey(0);
    return 0;
}