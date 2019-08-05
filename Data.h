#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "Value.h"
//#include "HOG.h"

using namespace std;
using namespace cv;

class ImageData
{
	Mat _image1;	Mat _image2;
	Mat c_image1;	Mat c_image2;
public:
	void Set_Images(Mat &image1, Mat &image2);
	Mat Get_Image1();	Mat Get_Image2();

	void Set_CImage1(Mat &image);
	void Set_CImage2(Mat &image);
	Mat Get_CImage1();	Mat Get_CImage2();
};

class Img1_Data
{
private:	
	vector<Moravec_Data> keypoint1;	Mat moravec_dbl;
	vector<vector<double>> hist1;

public:	
	void Set_moravec_dbl(Mat _dbl);
	Mat Get_moravec_dbl() {	return moravec_dbl;	}

	void Set_keypoint1(const vector<Moravec_Data> &vector);
	vector<Moravec_Data> Get_keypoint1()	{ return keypoint1; }
	
	Moravec_Data GetPosition1(int idx)
	{
		if (0 > idx || idx > keypoint1.size())
			std::cout << "肋给等 Idx 立辟" << std::endl;
		return keypoint1[idx];
	}
	
	vector<vector<double>> Get_hist1()	{	return hist1;	}

};

class Img2_Data
{
private:
	vector<Moravec_Data> keypoint2;	Mat moravec_dbl;
	vector<vector<double>> hist2;

public:
	void Set_moravec_dbl(Mat _dbl);
	Mat Get_moravec_dbl()	{	return moravec_dbl;	}
	
	void Set_keypoint2(const vector<Moravec_Data> &vector);
	vector<Moravec_Data> Get_keypoint2()
	{
		return keypoint2;
	}

	Moravec_Data GetPositdaion2(int idx)
	{
		if (0 > idx || idx > keypoint2.size())
			std::cout << "肋给等 Idx 立辟" << std::endl;
		return keypoint2[idx];
	}	
};
