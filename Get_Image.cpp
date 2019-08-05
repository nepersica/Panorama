#include "Data.h"
#include "Get_Image.h"

Mat Image::ImageToGray(Mat image)
{
	cv::cvtColor(image, image, CV_BGR2GRAY);
	return image;
}

ImageData Image::ReadImage()
{
	ImageData data;

	Mat InputImage1 = cv::imread("�ҳ�ô� 1.jpg");
	Mat image1 = InputImage1.clone();
	data.Set_CImage1(image1);
	
	Mat InputImage2 = cv::imread("�ҳ�ô� 2.jpg");
	Mat image2 = InputImage2.clone();
	data.Set_CImage2(image2);

	data.Set_Images(ImageToGray(image1), ImageToGray(image2));
	
	return data;
}
