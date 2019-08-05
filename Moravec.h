#pragma once
#include <opencv2/opencv.hpp>
#include "Data.h"
#include <vector>

using namespace std;
using namespace cv;


class Moravec
{
private:
	
public:
	Mat Moravec_Algorithm(Mat image1);
	vector<Moravec_Data> N_Extract(const Mat &_dbl, Mat &_img);
};
