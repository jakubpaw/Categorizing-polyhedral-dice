#include <iostream>
#include <conio.h>
#include <opencv2/opencv.hpp>
#include "imageEditor.h"
#include "EFilterName.h"
using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("input/testread.jpg");
	cout << img.rows << "   " << img.cols << endl;

	ImageEditor editor(img);
	Mat newImg = editor.detectEdges(LaplaceFilter1);
	
	imwrite("output/testwrite.jpg", newImg);

	namedWindow("image", 0);
	imshow("image", newImg);
	waitKey();
}