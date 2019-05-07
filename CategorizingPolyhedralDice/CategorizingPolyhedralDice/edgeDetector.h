#pragma once
#include <opencv2/opencv.hpp>
#include "EFilterName.h"
using namespace cv;

class EdgeDetector
{
private:
	Mat image;
	float** mask;
	void makeCleanMask(int size);
	void makeImageEdgesBlack(Mat image);


public:
	EdgeDetector(Mat img)
	{
		image = img;
		mask = NULL;
	}
	~EdgeDetector()
	{
		delete mask;
	}
	void makeLaplaceFilterMask1();
	void makeLaplaceFilterMask2();
	void makeHorizontalPrewwitFilterMask();
	void makeVerticalPrewwitFilterMask();

	void makeMask(int size, int centerValue, int cornerValue, int otherValue);
	Mat detect();
};