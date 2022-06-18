#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>

using namespace std;
using namespace cv;

Mat src;
int i=80;
int main()
{
	VideoCapture capture;
	capture.open(0);
	if(capture.isOpened())
	{
		while(1)
		{
			capture >> src;
			imshow("src", src);
			if(waitKey(5) == 49)
			{
				imwrite("../"+to_string(i)+".jpg", src);
				i++;
			}
			else if(waitKey(5) >=0 )
				break;
		}
	}
}
