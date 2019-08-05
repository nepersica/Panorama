#include "Data.h"
#include "Moravec.h" 
#include "HOG.h"

void ImageData::Set_Images(Mat &image1, Mat &image2)
{
	_image1 = image1.clone();
	_image2 = image2.clone();
}

Mat ImageData::Get_Image1()
{
	return _image1;
}
Mat ImageData::Get_Image2()
{
	return _image2;
}

void ImageData::Set_CImage1(Mat &image)
{
	c_image1 = image.clone();
}

void ImageData::Set_CImage2(Mat &image)
{
	c_image2 = image.clone();
}

Mat ImageData::Get_CImage1()
{
	return c_image1;
}
Mat ImageData::Get_CImage2()
{
	return c_image2;
}

void Img1_Data::Set_moravec_dbl(Mat _dbl)
{
	moravec_dbl = _dbl.clone();
}

void Img1_Data::Set_keypoint1(const vector<Moravec_Data> &vector)
{
	this->keypoint1.assign(vector.begin(), vector.end());
}

void Img2_Data::Set_moravec_dbl(Mat _dbl)
{
	moravec_dbl = _dbl.clone();
}

void Img2_Data::Set_keypoint2(const vector<Moravec_Data> &vector)
{
	this->keypoint2.assign(vector.begin(), vector.end());
}
