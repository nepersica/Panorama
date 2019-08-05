#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;

//class Position
//{
//protected:
//	std::pair<int, int> position;
//
//public:
//	std::pair<int, int> GetPosition()
//	{
//		return position;
//	}
//};

class Moravec_Data
{
private:
	double value;
	cv::Point position;

public:
	Moravec_Data() {}
	Moravec_Data(double value, cv::Point position)
	{
		this->value = value;
		this->position = position;
	}
	const cv::Point Get_Position() const
	{
		return position;
	}

	cv::Point Get_Position(vector<Moravec_Data> vector, int idx)
	{
		return vector.at(idx).position;
	}
	static bool Compare(const Moravec_Data& v1, const Moravec_Data& v2)
	{
		return v1.value > v2.value;
	}

	double GetValue()
	{
		return value;
	}
	
};

class Euclidean_Data
{
private:
	vector<Euclidean_Data> matching_data;
	cv::Point img1_px;	cv::Point img2_px;

public:
	Euclidean_Data(){};
	Euclidean_Data(cv::Point img1_px, cv::Point img2_px)
	{
		this->img1_px = img1_px;
		this->img2_px = img2_px;
	}


	void Set_distanceV(vector<Euclidean_Data> vector)
	{
		this->matching_data = vector;
	}

	vector<Euclidean_Data> Get_distanceV()	{	return matching_data;	}

	const cv::Point Get_Position1() const
	{
		return img1_px;
	}

	const cv::Point Get_Position2() const
	{
		return img2_px;
	}

	cv::Point Get_Position1(vector<Euclidean_Data> vector, int idx)
	{
		return vector.at(idx).img1_px;
	}

	cv::Point Get_Position2(vector<Euclidean_Data> vector, int idx)
	{
		return vector.at(idx).img2_px;
	}
};

class Homologous_pt
{
private:
	cv::Point img1_px;	cv::Point img2_px;
public:
	Homologous_pt()	{ };
	Homologous_pt(cv::Point img1_px, cv::Point img2_px)
	{
		this->img1_px = img1_px;
		this->img2_px = img2_px;
	}

	const cv::Point Get_Position1() const
	{
		return img1_px;
	}

	const cv::Point Get_Position2() const
	{
		return img2_px;
	}



};
