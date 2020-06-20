#pragma once

#ifndef PreProc

//includes
#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

//main class
static class PreProc 
{
public:
	static void process(std::string type, std::vector<cv::Mat> *processed)
	{
		std::cout <<
			"READING::" << type << "\n";
		std::vector<cv::Mat> processed_images;
		cv::Mat image;
		int counter = 0;
		bool success = true;
		std::string path = "../../input/" + type + "/" + type + "-" + std::to_string(counter+1) + ".jpg";
		while(success)
		{
			std::string path = "../../input/" + type + "/" + type + "-" + std::to_string(counter+1) + ".jpg";
			success = seperate(path, &image);
			processed_images.push_back(image);
			counter++;
		}
		std::cout <<
			"COMPLETED " + std::to_string(counter - 1) + " IMAGES\n";
	}
private:
	static bool seperate(std::string imagename, cv::Mat *imageoutput, bool silent = false, bool custom = false)
	{
		cv::Mat bgdModel, fgdModel;
		cv::Mat mask;
		//load the image
		cv::Mat image;
		try
		{
			image = cv::imread(imagename, CV_64FC1);
		}
		catch (...)
		{
			return false;
		}
		if (image.cols == 0)
		{
			return false;
		}

		//rectangle for opencv
		cv::Rect rectangle = cv::Rect(1, 1, image.size[1]-1, image.size[0]-1);

		//grabcut section, takes in image and foreground rect and outputs to mask
		cv::grabCut(image, mask, rectangle, bgdModel, fgdModel, 5, cv::GC_INIT_WITH_RECT);
		cv::compare(mask, cv::GC_PR_FGD, mask, cv::CMP_EQ);
		//end grabcut

		//take mask and image and return a masked image
		cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(0, 0, 0));
		image.copyTo(foreground, mask);
		
		//display
		cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
		cv::imshow("Display window", foreground);
		cv::waitKey(0);

		//output image generation
		*imageoutput = foreground;
		return true;
	}
};

#endif // !PreProc