#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <iterator>
#include <stdexcept>

#include "PsilLang.h"

class FileManager
{
public:
	//Read a strategy from file into a map (line number mapped to line string)
	static void readFromFile(const std::string& filePath, std::map<int, std::string>& strategy);
	//Write a strategy map to file
	static void writeToFile(const std::string& filePath, const std::map<int, std::string>& strategy);
	//Write a string to file
	static void writeToFile(const std::string& filePath, const std::string& s);
	//Get the name of a file from a file path
	static const std::string getFileName(const std::string& filePath);
};