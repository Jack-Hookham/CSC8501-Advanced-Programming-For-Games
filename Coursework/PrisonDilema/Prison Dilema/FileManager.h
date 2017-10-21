#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <iterator>

#include "PsilLang.h"

class FileManager
{
public:
	static void readFromFile(const std::string& filePath, std::map<int, std::string>& strategy);
	static void writeToFile(const std::string& filePath, const std::map<int, std::string>& strategy);
};