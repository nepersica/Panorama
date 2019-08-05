#pragma once
#include <opencv2/opencv.hpp>
#include "Data.h"

using namespace std;
using namespace cv;

class Image
{

public:
	Mat ImageToGray(Mat image);
	ImageData ReadImage();

};