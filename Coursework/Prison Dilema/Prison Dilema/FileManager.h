#pragma once

#include <fstream>
#include <string>
#include <iostream>

class FileManager
{
public:
	static void readFileToArray(std::string filePath, std::string lines[]);
};