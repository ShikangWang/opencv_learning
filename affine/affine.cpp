#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat src(600,600,CV_8UC3);
    Mat img = imread("/home/wsk/codes/cv_learning/read_img/test.jpg");
    int row, col;
    row = img.rows;
    col = img.cols;
    Point2f src2_points[3] = {Point2f(0,row), Point2f(col,row), Point2f(col,0)};
    Point2f dst2_points[3] = {Point2f(0,row), Point2f(col/2,row), Point2f(col,0)};
    Mat M2 = getAffineTransform(src2_points, dst2_points);
    Mat dst;
    Size size2(col, row);
    warpAffine(img, dst, M2, size2);
    imshow("affine", dst);

    waitKey(0);
    return 0;
}