#include <iostream>
#include <opencv2/opencv.hpp>
#include "Data.h"
#include "Value.h"
#include "Get_Image.h"
#include "Moravec.h"
#include "HOG.h"
#include "Euclidean.h"
#include "Ransac.h"
#include <vector>

using namespace std;
using namespace cv;


int main()
{
	Image image;
	ImageData img_data = image.ReadImage();

	Img1_Data data1; Img2_Data data2;

	Moravec moravec;
	data1.Set_moravec_dbl(moravec.Moravec_Algorithm(img_data.Get_Image1()));
	data1.Set_keypoint1(moravec.N_Extract(data1.Get_moravec_dbl(), img_data.Get_Image1()));
	data2.Set_moravec_dbl(moravec.Moravec_Algorithm(img_data.Get_Image2()));
	data2.Set_keypoint2(moravec.N_Extract(data2.Get_moravec_dbl(), img_data.Get_Image2()));

	HOG hog;
	vector<HOG_DATA> hog1_img = hog.HOG_Algorithm(img_data.Get_Image1(), data1.Get_keypoint1());
	vector<HOG_DATA> hog2_img = hog.HOG_Algorithm(img_data.Get_Image2(), data2.Get_keypoint2());

	Euclidean euclidean;	Euclidean_Data e_data;
	vector<Euclidean_Data> euclideanVec = euclidean.Extract_MinDistance(hog1_img, hog2_img);
	euclidean.Matching(euclideanVec, img_data.Get_Image1(), img_data.Get_Image2());

	Ransac ransac;
	Mat T = ransac.Ransac_Algorithm(euclideanVec);
	Mat _T = T.inv();

	Mat InputImage1 = img_data.Get_CImage1();
	Mat InputImage2 = img_data.Get_CImage2();

	Mat result = cv::Mat::zeros(InputImage1.rows, 700 , CV_8UC3);

	Mat A(1, 3, CV_64FC1);
	A.at<double>(0, 0) = InputImage2.rows - 1;
	A.at<double>(0, 1) = InputImage2.cols - 1;
	A.at<double>(0, 2) = 1;

	Mat trans = A * _T;

	for (int y = 0; y < InputImage1.rows; y++)
	{
		for (int x = 0; x < InputImage1.cols; x++)
		{
			result.at<Vec3b>(y, x) = InputImage1.at<Vec3b>(y, x);
		}
	}

	pair<int, int> win;
	int result_x = 0;
	int result_y = 0;
	int _x = 0;
	int _y = 0;
	for (int y = 0; y < InputImage2.rows; y++)
	{
		for (int x = 0; x < InputImage2.cols; x++)
		{
			Mat A(1, 3, CV_64FC1);
			A.at<double>(0, 0) = y;
			A.at<double>(0, 1) = x;
			A.at<double>(0, 2) = 1;

			Mat trans = A * _T;
			_x = trans.at<double>(0, 1);
			_y = trans.at<double>(0, 0);
			/*
			if (_x < 0)
				_x = 0;

			if (_y < 0)
				_y = 0;

			if (_x > result.cols - 1)
				_x = result.cols - 1;

			if (_y > result.rows - 1)
				_y = result.rows - 1;
*/
			result.at<Vec3b>(_y, _x) = InputImage2.at<Vec3b>(y, x);

		}
	}
	Mat dst;
	
	imshow("TEst", result(Range(0, _y), Range(0, _x)));
	waitKey();

	return 0;
}