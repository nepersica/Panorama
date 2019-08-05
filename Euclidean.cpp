#include "Euclidean.h"
#include <vector>

using namespace std;
using namespace cv;


vector<Euclidean_Data> Euclidean::Extract_MinDistance(const vector<HOG_DATA>& img_HOG1, const vector<HOG_DATA>& img_HOG2)
{
	Moravec_Data m_data;
	vector<Euclidean_Data> vector;
	double threshold = 1650;

	for (auto h1 : img_HOG1)
	{
		double min_distance = DBL_MAX;
		cv::Point pt;
		for (auto h2 : img_HOG2)
		{
			double distance = Calculate_distance(h1.HOG, h2.HOG);

			if (min_distance > distance)
			{
				min_distance = distance;
				pt = h2.pt;
			}
		}

		if (threshold >  min_distance)
		{
			Euclidean_Data data{ h1.pt, pt };
			vector.push_back(data);
		}
	}	

	return vector;
}

double Euclidean::Calculate_distance(const vector<double> &hist1, const vector<double> &hist2)
{

	double result = 0;
	for (int i = 0; i < hist1.size(); i++)
	{ 
		double hist1_bin_value = hist1.at(i);	
		double hist2_bin_value = hist2.at(i);

		result += sqrt(pow((hist1_bin_value - hist2_bin_value), 2));
	}

	return result;
}

void Euclidean::Matching(const vector<Euclidean_Data> vector, Mat &image1, Mat &image2)
{
	
	cv::namedWindow("Test", WINDOW_NORMAL);
	
	Mat result;
	hconcat(image1, image2, result);

	cvtColor(result, result, CV_GRAY2RGB);
	
	for (auto v : vector)
	{
		cv::Point img1_px = v.Get_Position1();
		cv::Point img2_px = v.Get_Position2();	

		line(result, Point(img1_px.x, img1_px.y),
			Point(img2_px.x + image1.cols, img2_px.y), Scalar(0, 255, 0));

		
	}

	/*imshow("Test", result);
	waitKey();*/

}