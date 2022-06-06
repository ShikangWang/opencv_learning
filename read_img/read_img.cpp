#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("/home/wsk/codes/cv_learning/read_img/test.jpg");
    imshow("test1", img);

    waitKey(0);
    return 0;
}
