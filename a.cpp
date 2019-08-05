uchar img_c[12][12] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
Mat img = cv::Mat(12, 12, CV_8UC1, img_c);
cv::namedWindow("Test", WINDOW_NORMAL);
cv::namedWindow("Test2", WINDOW_NORMAL);
cv::namedWindow("Test3", WINDOW_NORMAL);
cv::namedWindow("Test4", WINDOW_NORMAL);
cv::namedWindow("Test5", WINDOW_NORMAL);
cv::imshow("Test", img);

for (int y = 2; y < 10; y++)
{
	for (int x = 2; x < 10; x++)
	{
		Mat f = img(cv::Rect(x - 1, y - 1, 3, 3));
		f.convertTo(f, CV_64FC1);
		f /= 255.;
		Mat img_copy = img.clone();
		cv::rectangle(img_copy, cv::Rect(x - 1, y - 1, 3, 3), 255);

		cv::imshow("Test2", f);
		cv::imshow("Test3", img_copy);

		for (int u = -1; u <= 1; u++)
		{
			for (int v = -1; v <= 1; v++)
			{
				Mat f_neighbor = img(cv::Rect(x + v - 1, y + u - 1, 3, 3));
				f_neighbor.convertTo(f_neighbor, CV_64FC1);	// double 타입으로 변환.
				f_neighbor /= 255.;

				cout << "f" << endl;
				cout << f << endl;

				cout << "f_neighbor" << endl;
				cout << f_neighbor << endl;

				Mat diff;
				cv::subtract(f, f_neighbor, diff);

				cout << "diff" << endl;
				cout << diff << endl;

				Mat mat_pow;
				cv::pow(diff, 2, mat_pow);
				double s = cv::sum(mat_pow)[0];

				cout << "mat_sqrt" << endl;
				cout << mat_pow << endl;

				cout << "sum" << endl;
				cout << s << endl;

				Mat img_copy2 = img.clone();
				cv::rectangle(img_copy2, cv::Rect(x + v - 1, y + u - 1, 3, 3), 255);
				cv::imshow("Test4", f_neighbor);
				cv::imshow("Test5", img_copy2);
				cv::waitKey();
			}
		}
	}
}


for (int y = 1; y < 11; y++)
{
	for (int x = 1; x < 11; x++)
	{
		Mat img_copy = img.clone();
		Mat f = img(cv::Rect(x - 1, y - 1, 3, 3));
		Mat rectImg;
		cv::rectangle(img_copy, cv::Rect(x - 1, y - 1, 3, 3), 255);

		cv::imshow("Test2", f);
		cv::imshow("Test3", f);
		cv::waitKey();
	}
}

//for (int u = -1; u <= 1; u++)
//{
//	for (int v = -1; v <= 1; v++)
//	{
//		Mat now_neighbor = _image(cv::Rect(x + v - 1, y + u - 1, 3, 3)).clone();
//		now_neighbor.convertTo(now_neighbor, CV_64FC1);
//		now_neighbor /= 255.;

//		Mat diff;
//		subtract(now, now_neighbor, diff);

//		Mat mat_pow;
//		pow(diff, 2, mat_pow);
//		double s = sum(mat_pow)[0];

//		S.at<double>(u + 1, v + 1) = s;
//		
//		Mat img_copy2;
//		_image.copyTo(img_copy2);
//		rectangle(img_copy2, Rect(x + v - 1, y + u - 1, 3, 3), 255);
//		//imshow("Test4", now_neighbor);
//		//imshow("Test5", img_copy2);

//		//waitKey();
//	}
//}






#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

class Position
{
protected:
	std::pair<int, int> position;

public:
	Position()
	{
	}
	Position(std::pair<int, int> position)
		:position(position)
	{
	}
	std::pair<int, int> GetPosition()
	{
		return position;
	}
};

class Moravec_Data
{
private:
	double value;
	/*std::vector<Position> positionVec;*/
	std::pair<int, int> position;

public:
	Moravec_Data()
	{
	}
	Moravec_Data(double value)
		:value(value)
	{
	}
	static bool Compare(const Moravec_Data& v1, const Moravec_Data& v2)
	{
		return v1.value > v2.value;
	}



	/*void PushBack(std::pair<int, int> position)
	{
	positionVec.push_back(Position(position));
	}

	std::vector<Position> GetPositionVec()
	{
	return positionVec;
	}*/

};


concat_img = cv2.hconcat([img, img2])
for mp in euclidean :
test = concat_img.copy()
test = cv2.line(test, (mp.img1_coordinates[0], mp.img1_coordinates[1]),
(mp.img2_coordinates[0] + img.shape[1], mp.img2_coordinates[1]),
(255, 0, 0), 1).copy()
cv2.namedWindow("concat_img", cv2.WINDOW_NORMAL)
cv2.imshow("concat_img", test)
cv2.waitKey(0)