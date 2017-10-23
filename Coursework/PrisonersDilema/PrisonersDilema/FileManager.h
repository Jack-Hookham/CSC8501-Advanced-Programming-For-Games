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
	static void readFromFile(const std::string& const filePath, std::map<int, std::string>& const strategy);
	static void writeToFile(const std::string& const filePath, const std::map<int, std::string>& const strategy);
	static void writeToFile(const std::string& const filePath, const std::string& const s);
	static const std::string getFileName(const std::string& const filePath);
};