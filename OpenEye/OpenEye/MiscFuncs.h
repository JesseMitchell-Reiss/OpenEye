#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "datatypes.h"

std::vector<std::string> splitstr(std::string input, const char delim = ' ')
{
    std::vector<std::string> output;
    std::string temp = "";
    for (const char i : input)
    {
        if (i == delim)
        {
            output.push_back(temp);
            temp = "";
        }
        else
        {
            temp += i;
        }
    }
    output.push_back(temp);
    return output;
}

bool vectContains(std::vector<std::string> in, std::string arg)
{
	if (count(in.begin(), in.end(), arg))
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::vector<Detection> nms(std::vector<Detection> inputRects, float thresh)
{
    return inputRects;
}