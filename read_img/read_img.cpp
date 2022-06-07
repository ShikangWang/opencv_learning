#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("../../ball.jpg");
    imshow("test1", img);

    waitKey(0);
    return 0;
}
