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

	Mat greyImg2;
	cvtColor(img, greyImg2, COLOR_BGR2GRAY);
	namedWindow("image", 0);
	imshow("image", greyImg2);
	waitKey();

	ImageEditor editor(greyImg2);
	Mat newImg = editor.detectEdges(VerticalPrewwitFilter);
	
	imwrite("output/testwrite.jpg", newImg);

	namedWindow("image", 0);
	imshow("image", newImg);
	waitKey();
	Mat greyImg;
	cvtColor(newImg, greyImg, COLOR_BGR2GRAY);
	namedWindow("image", 0);
	imshow("image", greyImg);
	waitKey();
}