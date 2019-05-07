#include "imageEditor.h"
#include "edgeDetector.h"
using namespace std;
Mat ImageEditor::detectEdges(EFilterName filterName)
{
	EdgeDetector detector(image);
	switch (filterName)
	{
	case LaplaceFilter1:
		detector.makeLaplaceFilterMask1();
		break;
	case LaplaceFilter2:
		detector.makeLaplaceFilterMask2();
		break;
	case HorizontalPrewwitFilter:
		detector.makeHorizontalPrewwitFilterMask();
		break;
	case VerticalPrewwitFilter:
		detector.makeVerticalPrewwitFilterMask();
		break;
	default:
		cout << "Error: bad EFilterName in detectEdges method" << endl;
		return image;
	}
	return (detector.detect());
}