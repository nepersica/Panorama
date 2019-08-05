#include "Ransac.h"
#include "Value.h"
#include <random>

using namespace std;
using namespace cv;

Mat Ransac::Ransac_Algorithm(vector<Euclidean_Data> &data)
{	
	Euclidean_Data e_data;

	random_device _num;		mt19937_64 NUM(_num());
	uniform_real_distribution<> PICK_NUM_RANDOMLY(0, data.size());

	vector<Mat> T_vector;
	Mat best_t;
	double min_error= DBL_MAX;
	for (int i = 0; i < 1000; i++)
	{
		std::vector<Homologous_pt> extract_pt;
		std::vector<int> ranVec;
		std::vector<Homologous_pt> inliner;

		int count = 0;
		while (count != 3)		// line 3
		{
			int idx = PICK_NUM_RANDOMLY(NUM);
			if (find(ranVec.begin(), ranVec.end(), idx) == ranVec.end())
			{
				ranVec.push_back(idx);
				Homologous_pt points{ data.at(idx).Get_Position1() , data.at(idx).Get_Position2() };
				extract_pt.push_back(points);	count++;
			}
		}

		Mat T = Calculate_MatrixT(extract_pt);	// line 4


		inliner.assign(extract_pt.begin(), extract_pt.end());

		for (int i = 0; i < data.size(); i++)
		{
			if (find(ranVec.begin(), ranVec.end(), i) == ranVec.end())	// line 7
			{
				if (Get_Error(T, data.at(i)) < 1.)
				{
					Homologous_pt points{ data.at(i).Get_Position1() , data.at(i).Get_Position2() };
					inliner.push_back(points);
				}
			}
		}

		if (inliner.size() > data.size() * 0.7)
			T = Calculate_MatrixT(inliner);

		double error_sum = 0;
		for (int i = 0; i < data.size(); i++)
		{
			error_sum += Get_Error(T, data.at(i));
		}

		cout << "error_sum : " << error_sum << endl;
		if (error_sum < min_error)
		{			
			min_error = error_sum;
			best_t = T.clone();
		}
	}	

	Mat _T = Mat::zeros(3, 3, CV_64FC1);
	_T.at<double>(0, 0) = best_t.at<double>(0);	_T.at<double>(0, 1) = best_t.at<double>(3);
	_T.at<double>(1, 0) = best_t.at<double>(1);	_T.at<double>(1, 1) = best_t.at<double>(4);
	_T.at<double>(2, 0) = best_t.at<double>(2);	_T.at<double>(2, 1) = best_t.at<double>(5);
	_T.at<double>(2, 2) = 1;

	std::cout << _T << std::endl;
	std::cout << _T.inv() << std::endl;
	return _T;
}

double Ransac::Get_Error(Mat &T, Euclidean_Data pts)
{
	Mat _B;
	Mat A(1, 3, CV_64FC1);
	A.at<double>(0, 0) = pts.Get_Position1().y;
	A.at<double>(0, 1) = pts.Get_Position1().x;
	A.at<double>(0, 2) = 1;

	Mat _T = Mat::zeros(3, 3, CV_64FC1);
	_T.at<double>(0, 0) = T.at<double>(0, 0);	_T.at<double>(0, 1) = T.at<double>(3, 0);
	_T.at<double>(1, 0) = T.at<double>(1, 0);	_T.at<double>(1, 1) = T.at<double>(4, 0);
	_T.at<double>(2, 0) = T.at<double>(2, 0);	_T.at<double>(2, 1) = T.at<double>(5, 0);
	_T.at<double>(2, 2) = 1;

	_B = A * _T;	// 1x3

	double error;
	error = pow((_B.at<double>(0, 0) - pts.Get_Position2().y), 2) + pow((_B.at<double>(0, 1) - pts.Get_Position2().x), 2);

	return error;
}

Mat Ransac::Calculate_MatrixT(vector<Homologous_pt> extract_points)
{
	Mat A = Mat::zeros(6, 6, CV_64FC1);
	Homologous_pt data;

	// Make A
	for (auto& v : extract_points)
	{
		cv::Point pt = v.Get_Position1();
		
		int a1 = pt.y;
		int a2 = pt.x;

		A.at<double>(0, 0) += (a1 * a1);	 A.at<double>(0, 1) += (a1 * a2);	 A.at<double>(0, 2) += (a1);
		A.at<double>(1, 0) += (a1 * a2);	 A.at<double>(1, 1) += (a2 * a2);	 A.at<double>(1, 2) += (a2);
		A.at<double>(2, 0) += (a1);			 A.at<double>(2, 1) += (a2);		 A.at<double>(2, 2) +=1;

		A.at<double>(3, 3) += (a1 * a1);	 A.at<double>(3, 4) += (a1 * a2);	 A.at<double>(3, 5) += (a1);
		A.at<double>(4, 3) += (a1 * a2);	 A.at<double>(4, 4) += (a2 * a2);	 A.at<double>(4, 5) += (a2);
		A.at<double>(5, 3) += (a1);			 A.at<double>(5, 4) += (a2);		 A.at<double>(5, 5) += 1;
	}

	Mat A_inv = A.inv();

	Mat B = Mat::zeros(6, 1, CV_64FC1);
	// Make B
	for (auto& v : extract_points)
	{
		cv::Point pt1 = v.Get_Position1();
		cv::Point pt2 = v.Get_Position2();

		int a1 = pt1.y;		int a2 = pt1.x;
		int b1 = pt2.y;		int b2 = pt2.x;

		B.at<double>(0, 0) += (a1 * b1);	 
		B.at<double>(1, 0) += (a2 * b1);
		B.at<double>(2, 0) += (b1);		
		B.at<double>(3, 0) += (a1 * b2);
		B.at<double>(4, 0) += (a2*b2);	
		B.at<double>(5, 0) += (b2);

	}

	Mat result = A_inv * B; 

 	return result.clone();

}