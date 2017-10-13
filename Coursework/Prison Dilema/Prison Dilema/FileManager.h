#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

//Manages file IO

class FileManager
{
public:
	//Used by Shader to read shader files
	static bool readFile(std::string filePath, std::string& buffer);
};