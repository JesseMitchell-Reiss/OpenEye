#pragma once

#ifndef Detect

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/dnn.hpp>
#include <iomanip>
#include "datatypes.h"

static class Detect
{

public:
	static std::vector<Detection> objDetect(std::string file, bool silent = false, int displayTime = 0, float threshold = 0.5, float nms = 0.4)
	{
		cv::dnn::Net network = cv::dnn::readNet("../../../tensorflow/frozen_inference_graph.pb", "../../../tensorflow/ssd_mobilenet_v2_coco_2018_03_29.pbtxt");
		std::vector<Detection> objectsfound;
		cv::Mat objects = object(file, network, objectsfound, threshold, nms);
		if (!silent)
		{
			cv::namedWindow("Classified image", cv::WINDOW_AUTOSIZE);
			cv::imshow("Classified image", objects);
			cv::waitKey(displayTime);
		}
		if (network.empty())
		{
			std::cout << "No Network Found! Quitting Program." << std::endl;
			exit(0);
		}
		return objectsfound;
	}
private:
	static cv::Mat object(std::string file, cv::dnn::Net network, std::vector<Detection> &objects, float threshold = 0.5, float nms = 0.4)
	{
		//i need to add a json parser for the config, for now i am using a handmade vector of strings
		std::vector<std::string> list = { "background", "person", "bicycle", "car", "motercycle", "airplane", "bus", "train", "truck", "boat", "traffic light", "fire hydrant", "12", "stop sign", "parking meter", "bench", "bird", "cat", "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe", "26", "backpack", "umbrella", "29", "30", "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard", "sports ball", "kite", "baseball bat", "baseball glove", "skateboard", "surfboard", "tennis racket", "bottle", "45", "wine glass", "cup", "fork", "knife", "spoon", "bowl", "bananna", "apple", "sandwich", "orange", "brocolli", "carrot", "hot dog", "pizza", "donut", "cake", "chair", "couch", "potted plant", "bed", "66", "dining table", "68", "69", "toilet", "71", "tv", "laptop", "mouse", "remote", "keyboard", "cell phone", "microwave", "oven", "toaster", "sink", "refrigerator", "83", "book", "clock", "vase", "scissors", "teddy bear", "hair drier", "toothbrush" };
		std::vector<std::string> layers = network.getUnconnectedOutLayersNames();
		cv::Mat image = cv::imread(file);
		if (image.empty())
		{
			std::cout << "No Image Found! Quitting Program." << std::endl;
			exit(0);
		}
		cv::Mat output = image;
		cv::Mat blob = cv::dnn::blobFromImage(image);
		network.setInput(blob);
		cv::Mat blobout = network.forward(layers[0]);
		cv::Mat detections = cv::Mat(blobout.size[2], blobout.size[3], CV_32F, blobout.ptr<float>());
		for (int i = 0; i < detections.rows; i++)
		{
			if (detections.at<float>(i, 2) >= threshold)
			{
				//create a rect for the box
				float x1 = detections.at<float>(i, 3) * image.cols;
				float y1 = detections.at<float>(i,4) * image.rows;
				float x2 = detections.at<float>(i, 5) * image.cols;
				float y2 = detections.at<float>(i, 6) * image.rows;
				//make sure bbox is inside image fully
				if (x1 < 0)
				{
					x1 = 0;
				}
				if (x2 > image.rows)
				{
					x2 = image.rows;
				}
				if (y1 < 0)
				{
					y1 = 0;
				}
				if (y2 > image.cols)
				{
					y2 = image.cols;
				}
				cv::Point origin = cv::Point(x1, y1);
				cv::Point corner = cv::Point(x2, y2);
				cv::Rect bbox(origin, corner);
				//draw the bounding box on the image
				cv::rectangle(output, bbox, cv::Scalar(0, 255, 0), 3);
				//create the text string
				std::string type = list[int(detections.at<float>(i, 1))];
				int probability = int(detections.at<float>(i, 2) * 100);
				std::string toimage = type + ", " + std::to_string(probability) + "%";
				//put the text to the screen
				cv::putText(output, toimage, origin + cv::Point(0, 10), cv::HersheyFonts::FONT_HERSHEY_COMPLEX, 0.35, cv::Scalar(0, 255, 0));
				Detection temp = Detection(bbox, probability, type);
				objects.push_back(temp);
			}
		}
		return output;
	}
};

#endif // !Detect
