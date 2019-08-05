#pragma once
#include <opencv2/opencv.hpp>
#include "Value.h"
#include "HOG.h"
using namespace std;
using namespace cv;

class Euclidean
{
public:
	vector<Euclidean_Data> Extract_MinDistance(const vector<HOG_DATA> &img_HOG1, 
		const vector<HOG_DATA> &img_HOG2);
	double Calculate_distance(const vector<double> &hist1, const vector<double> &hist2);
	void Matching(const vector<Euclidean_Data> vector, Mat &image1, Mat &image2);
};