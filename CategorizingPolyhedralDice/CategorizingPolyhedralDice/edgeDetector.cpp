#include "edgeDetector.h"
using namespace std;

void EdgeDetector::makeMask(int size, int centerValue, int cornerValue, int otherValue)
{
	if (size % 2 == 0) cout << "WARNING!!! size can't be even" << endl;
	if (mask != NULL) delete mask;

	int centerIndex = size / 2 + 1;
	mask = new float*[size];
	for (int i = 0; i < size; i++)
	{
		mask[i] = new float[size];
		for (int j = 0; j < size; j++)
		{
			mask[i][j] = otherValue;
		}
	}
	mask[0][size - 1] = cornerValue;
	mask[0][0] = cornerValue;
	mask[size - 1][0] = cornerValue;
	mask[size - 1][size - 1] = cornerValue;
	mask[centerIndex][centerIndex] = centerValue;

	maskSize = size;
}

void EdgeDetector::makeCleanMask(int size)
{
	if (size % 2 == 0) cout << "WARNING!!! size can't be even" << endl;
	if (mask != NULL) delete mask;

	maskSize = size;

	mask = new float*[size];
	for (int i = 0; i < size; i++)
	{
		mask[i] = new float[size];
	}
}

void EdgeDetector::makeLaplaceFilterMask1()
{
	makeMask(3, 4, 0, -1);
}

void EdgeDetector::makeLaplaceFilterMask2()
{
	makeMask(3, 8, -1, -1);
}

void EdgeDetector::makeVerticalPrewwitFilterMask()
{
	int size = 3;
	makeCleanMask(size);
	for (int i = 0; i < size; i++)
	{
		mask[0][i] = -1;
		mask[1][i] = 0;
		mask[2][i] = 1;
	}
}

void EdgeDetector::makeHorizontalPrewwitFilterMask()
{
	int size = 3;
	makeCleanMask(size);
	for (int i = 0; i < size; i++)
	{
		mask[i][0] = -1;
		mask[i][1] = 0;
		mask[i][2] = 1;
	}
}

Mat EdgeDetector::detect()
{
	if (mask == NULL)
	{
		cout << "no mask" << endl;
		return image;
	}
	Mat newImage = image.clone();
	makeImageEdgesBlack(newImage);
	int halfMaskSize = maskSize / 2;
	for (int x = halfMaskSize; x < newImage.cols - halfMaskSize; x++)
	{
		for (int y = halfMaskSize; y < newImage.rows - halfMaskSize; y++)
		{
			newImage.at<Vec3b>(x,y) = calculatePixelRGBValues(image, x, y);
		}
	}

	return newImage;
}

Vec3b EdgeDetector::calculatePixelRGBValues(Mat img, int pixelX, int pixelY)
{
	int blue = 0;
	int red = 0;
	int green = 0;
	int maskWeightSum = 0;
	int halfMaskSize = maskSize / 2;
	int startX = pixelX - halfMaskSize;
	int startY = pixelY - halfMaskSize;
	for (int x = 0; x < maskSize; x++)
	{
		for (int y = 0; y < maskSize; y++)
		{
			Vec3b color = image.at<Vec3b>(x + startX, y + startY);
			blue+=color.val[0]*mask[x][y];
			green += color.val[1] * mask[x][y];
			red += color.val[2] * mask[x][y];
			maskWeightSum += mask[x][y];
		}
	}
	
	//return Vec3b(blue/maskWeightSum, green/maskWeightSum, red/maskWeightSum);
	return Vec3b(blue, green, red);
}

void EdgeDetector::makeImageEdgesBlack(Mat image)
{
	int halfMaskSize = maskSize / 2;
	Vec3b color(0, 0, 0);
	//color.val[0] = 0; //blue
	//color.val[1] = 0; //green
	//color.val[2] = 0; //red
	for (int x = 0; x < image.cols; x++)
	{
		for (int y = 0; y < halfMaskSize; y++)
		{
			image.at<Vec3b>(x, y) = color;
			image.at<Vec3b>(x, image.rows - 1-y) = color;
		}
	}
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x< halfMaskSize; x++)
		{
			image.at<Vec3b>(x, y) = color;
			image.at<Vec3b>(image.cols - 1-x, y) = color;
		}
	}
	/*imwrite("output/testwrite2.jpg", image);*/
}