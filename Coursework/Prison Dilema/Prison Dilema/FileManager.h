#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <vector>

class FileManager
{
public:
	static void readFromFile(std::string filePath, std::vector<std::string>& strategy);
	static void writeToFile(std::string filePath, int lines, std::vector<std::string>& strategy);
};