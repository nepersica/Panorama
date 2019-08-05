#pragma once
#include <opencv2/opencv.hpp>
#include "Data.h"
#include <vector>

using namespace std;
using namespace cv;

class Ransac
{
public:
	Mat Ransac_Algorithm(vector<Euclidean_Data> &data);
	Mat Calculate_MatrixT(vector<Homologous_pt> extract_points);
	double Get_Error(Mat &T, Euclidean_Data pts);
};