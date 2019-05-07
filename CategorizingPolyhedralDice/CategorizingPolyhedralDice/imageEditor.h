#pragma once
#include <opencv2/opencv.hpp>
#include "EFilterName.h"
using namespace cv;
class ImageEditor
{
private:
	Mat image;


public:
	ImageEditor(Mat img)
	{
		image = img;
	}
	Mat detectEdges(EFilterName filterName);
};