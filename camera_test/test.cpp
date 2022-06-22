#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat src;

int main()
{
	VideoCapture capture;
	capture.open(0);

	if(capture.isOpened())
	{
		while(1)
		{
			for (int i=0; i<3; i++)
				capture >> src;
			imshow("src", src);
			if(waitKey(5)>=0)
				break;
		}
	}
}

