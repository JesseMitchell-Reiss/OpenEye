#pragma once

#ifndef Training

#include <fstream>
#include <iostream>
#include "Preprocess.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/features2d.hpp>

static class Training
{
public:
	static void train(std::string type, bool preproc = true)
	{
		std::cout << "CREATING MODEL FOR: " + type << std::endl;
		std::string filedir = "../../Models.dot";
		std::vector<cv::Mat> outputvect; 

		cv::Mat temp;
		while (true)
		{
			temp = cv::imread("../../input/" + type + ".jpg", CV_64FC1);
			if (!temp.data)
			{
				break;
			}
			outputvect.push_back(temp);
		}
		generateTrainingFile(filedir, outputvect);
		std::cout << "MODEL FINISHED";
	}
private:
	static void generateTrainingFile(std::string path, std::vector<cv::Mat> imageset)
	{
		for (cv::Mat i : imageset)
		{
			cv::Mat blob = cv::dnn::blobFromImage(i);
			cv::dnn::Net nural;
		}
	}
};

#endif // !Training
