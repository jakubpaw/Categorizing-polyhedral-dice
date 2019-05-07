#pragma once
#include <opencv2/opencv.hpp>
#include "EFilterName.h"
using namespace cv;

class EdgeDetector
{
private:
	Mat image;
	int maskSize;
	float** mask;
	void makeCleanMask(int size);
	void makeImageEdgesBlack(Mat image);
	Vec3b calculatePixelRGBValues(Mat img, int x, int y);


public:
	EdgeDetector(Mat img)
	{
		image = img;
		mask = NULL;
		maskSize = 3;
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