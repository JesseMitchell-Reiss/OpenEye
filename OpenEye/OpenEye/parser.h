#pragma once
#include <iostream>
#include <sstream>
#include <vector>

class CommandLineParser
{
public:
	CommandLineParser(int argc, const char* const argv[], std::string keys)
	{
		argcount = argc;
		for (int i = 0; i < argc; i++)
		{
			argvector.push_back(argv[i]);
		}
		seperatekeys(keys);
	}
	bool has(std::string str)
	{

	}
private:
	int argcount;
	std::vector<std::string> argvector;
	std::vector<std::tuple<std::string, std::string, std::string>()> keylist;
	void seperatekeys(std::string keys)
	{
		
	}
};