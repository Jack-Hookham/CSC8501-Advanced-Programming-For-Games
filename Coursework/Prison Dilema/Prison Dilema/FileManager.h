#pragma once

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class FileManager
{
public:
	static void readFileToArray(string filePath, string lines[]);
};