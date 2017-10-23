#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <random>


#include "FileManager.h"
#include "PsilLang.h"

class StrategyGenerator
{
public:
	//generate n random strategies
	static void generate(int n);

private:
	static const std::string folderPath;

	//generate a single strategy
	static void generateStrategy(int pathIndex);

	//generate a PSIL if statement
	static std::string generateIf(const int currentLineNum, const int totalLines, std::mt19937 &randGenerator);
	static std::string intToString(const int x);
};

