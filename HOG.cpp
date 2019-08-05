#include "HOG.h"

using namespace std;
using namespace cv;

vector<HOG_DATA> HOG::HOG_Algorithm(Mat &image, const vector<Moravec_Data> keypoint)
{
	Moravec_Data value;

	Mat _image = image.clone();

	Mat img_gx; Mat img_gy;	// Calculate gradients gx, gy
	Sobel(_image, img_gx, CV_64FC1, 1, 0, 3);
	Sobel(_image, img_gy, CV_64FC1, 0, 1, 3);

	Mat magnitude;	Mat angle;
	cartToPolar(img_gx, img_gy, magnitude, angle, 1);	// magnitude, angle ÃßÃâ.

	vector<HOG_DATA> img_hist;

	int kernelSize = 13;
	int halfKernelSize = kernelSize / 2;
	
	for (int idx = 0; idx < keypoint.size(); idx++)
	{
		cv::Point key_center = cv::Point(value.Get_Position(keypoint, idx));				

		if ((key_center.y - halfKernelSize >= 0) && (key_center.x - halfKernelSize >= 0)
			&& (key_center.y + halfKernelSize <= image.cols - 1) && (key_center.x + halfKernelSize <= image.rows - 1))
		{
			Mat mask_Mag = magnitude(cv::Rect(key_center.x - halfKernelSize, key_center.y - halfKernelSize, kernelSize, kernelSize)).clone();
			Mat mask_Ang = angle(cv::Rect(key_center.x - halfKernelSize, key_center.y - halfKernelSize, kernelSize, kernelSize)).clone();

			vector<double> hist = Stack_Histogram(mask_Mag, mask_Ang);	// bin 9ÀÎ histogram ½×±â.
			img_hist.push_back(HOG_DATA(hist, key_center));
		}
	}
	return img_hist;
}

vector<double> HOG::Stack_Histogram(const Mat &magnitude, const Mat &angle)
{

	vector<double> hist(8);	

	for (int y = 0; y < magnitude.rows; y++)
	{
		for (int x = 0; x < magnitude.cols; x++)
		{
			double mag_px = magnitude.at<double>(y , x);
			double ang_px = angle.at<double>(y, x);

			int idx = (ang_px / 45);			

			hist[idx] += mag_px;
		}
	}	 		

 	return hist;
}