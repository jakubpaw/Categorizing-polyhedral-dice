#include "edgeDetector.h"
using namespace std;

void EdgeDetector::makeMask(int size, int centerValue, int cornerValue, int otherValue)
{
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
}
void EdgeDetector::makeCleanMask(int size)
{
	if (mask != NULL) delete mask;

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


	return newImage;
}

void EdgeDetector::makeImageEdgesBlack(Mat image)
{
	Vec3b color(0, 0, 0);
	//color.val[0] = 0; //blue
	//color.val[1] = 0; //green
	//color.val[2] = 0; //red
	for (int x = 0; x < image.rows; x++)
	{
		image.at<Vec3b>(x, 0) = color;
		image.at<Vec3b>(x, image.cols-1) = color;
	}
	for (int y = 0; y < image.cols; y++)
	{
		image.at<Vec3b>(0, y) = color;
		image.at<Vec3b>(image.rows-1, y) = color;
	}
	/*imwrite("output/testwrite2.jpg", image);*/
}