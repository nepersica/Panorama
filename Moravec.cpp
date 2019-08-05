#include "Moravec.h"
#include <vector>

using namespace std;

Mat Moravec::Moravec_Algorithm(Mat image)
{
	Mat _image = image.clone();
	
	Mat _result = Mat::zeros(_image.rows, _image.cols, CV_8UC1);
	Mat _result_dbl = Mat::zeros(_image.rows, _image.cols, CV_64FC1);
	cv::Point availablePointers[4]{ cv::Point(-1, 0), cv::Point(0, -1),
		cv::Point(0, 1), cv::Point(1, 0) };
		
	for (int y = 2; y < _image.rows - 2; y++)
	{				
		for (int x = 2; x < _image.cols - 2; x++)
		{
			auto rect = cv::Rect(x - 1, y - 1, 3, 3);
			Mat now = _image(cv::Rect(x - 1, y - 1, 3, 3)).clone();

			now.convertTo(now, CV_64FC1);
				
			Mat S = Mat::zeros(3, 3, CV_64FC1);

			for (auto p : availablePointers)
			{
				Mat now_neighbor = _image(cv::Rect(x + p.x - 1, y + p.y - 1, 3, 3)).clone();
				now_neighbor.convertTo(now_neighbor, CV_64FC1);

				Mat diff;
				subtract(now, now_neighbor, diff);

				Mat mat_pow;
				pow(diff, 2, mat_pow);
				double s = sum(mat_pow)[0];

				S.at<double>(p.y + 1, p.x + 1) = s;
								
			}

			double min = DBL_MAX; 	pair<int, int> min_position = make_pair(0, 0);
			for (int u = 0; u < 3; u++)
			{
				for (int v = 0; v < 3; v++)
				{
					if ((u == 0 && v == 1) || (u == 1 && v == 0) || (u == 1 && v == 2) || (u == 2 && v == 1))
					{
						if (S.at<double>(u, v) < min)
						{
							min = S.at<double>(u, v);
 							min_position.first = u;	min_position.second = v;
						}

					}
				}
			}
			_result_dbl.at<double>(y, x) = S.at<double>(min_position.first, min_position.second);
			uchar val = cv::max(0.0, cv::min(255.0, S.at<double>(min_position.first, min_position.second)));	// 0~255∑Œ πŸ≤„¡÷±‚.
			_result.at<uchar>(y, x) = val;
		} 
	}

	return _result_dbl;

}

vector<Moravec_Data> Moravec::N_Extract(const Mat &_result, Mat &_image)
{
	Mat _img = _image.clone();

	vector<Moravec_Data> vector;
	for (int y = 2; y < _result.rows - 2; y++)
	{
		for (int x = 2; x < _result.cols - 2; x++)
		{
			Moravec_Data value{_result.at<double>(y, x), cv::Point(x, y) };
			vector.push_back(value);
		}
	}
	std::sort(vector.begin(), vector.end(), Moravec_Data::Compare);
	
	cvtColor(_img, _img, CV_GRAY2RGB);

	Moravec_Data value; int count = 0; std::vector<Moravec_Data> selected;
	
	Img1_Data data;

	for (auto v : vector)
	{
		if (v.GetValue() > 42000)
		{
			cv::Point now = v.Get_Position();
			circle(_img, Point(now.x, now.y), 3, Scalar(0, 0, 255));
			selected.push_back(v);
		}		
	}

	/*cv::namedWindow("Test", WINDOW_NORMAL);
	imshow("Test", _img);
	waitKey();*/

	return selected;
}
