#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <mutex>
#include <thread>
#include <queue>

#include "miscfuncs.h"
#include "Preprocess.h"
#include "detect.h"
#include "datatypes.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//keys for cli parser
	const string keys =
		"{ help h usage ?	| | Print help message. }"
		"{ detect d			| | Detect objects within an image and highlight them. }"
		"{ silent s			| | Do not display images and only output detections as text. }" 
		"{ modelbin b		| ../../tensorflow/frozen_inference_graph.pb | Binary model file. }"
		"{ modeltxt x		| ../../tensorflow/ssd_mobilenet_v2_coco_2018_03_29.pbtxt | Human readable model file. }"
		"{ modelcfg c		| ../../tensorflow/| Model configuration file. }"
		"{ imagepath i		| ../../input/image-1.jpg | Path of image to detect objects in. }"
		"{ directory p		| ../../input/tensorflow/mscoco_complete_label_map.json | Directory of image set. }"
		"{ thresh			| 0.5 | Confidence threshold. }"
		"{ nms				| 0.4 | Non maximum supression threshold. }"
		"{ disp				| 0 | Image display time, 0 to wait for  a key to be pressed. }"
		;
	//create cli parser
	CommandLineParser parser(argc, argv, keys);
	parser.about("Object detection v1.0.0");
	//get inputs from cil parser
	//directories
	string imagepath = parser.get<string>("imagepath");
	string modelbin = parser.get<string>("modelbin");
	string modeltxt = parser.get<string>("modeltxt");
	string modelcfg = parser.get<string>("modelcfg");
	string directory = parser.get<string>("directory");
	//values
	//string thresh = parser.get<string>("thresh");
	//modes
	bool silent = false;
	if (parser.has("silent"))
		silent = true;
	//functions
	if (parser.has("detect"))
	{
		std::cout << imagepath << std::endl;
		Detect::objDetect(imagepath, silent/*, displaytime, thresh, nms*/);
	}
	if (parser.has("help"))
		parser.printMessage();
}