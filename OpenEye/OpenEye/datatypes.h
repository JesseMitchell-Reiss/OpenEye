#pragma once
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/core.hpp>

class Detection
{
public:
	cv::Rect bBox;
	int prob;
	std::string type;
	Detection(cv::Rect boundingBox, int probability, std::string objectType)
	{
		bBox = boundingBox;
		prob = probability;
		type = objectType;
	}
	Detection()
	{
		bBox = cv::Rect(-1, -1, -1, -1);
		prob = -1;
		type = "";
	}
};