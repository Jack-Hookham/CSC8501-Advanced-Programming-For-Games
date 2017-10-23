#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include "FileManager.h"
#include "PsilLang.h"
#include "Random.h"

class StrategyGenerator
{
public:
	//generate n random strategies
	//gangStrategy bool determines whether the strategies are for lone prisoners or for gang prisoners
	static void generate(const int n, const bool gangStrategy = false);

private:
	static const std::string prisonerPath;
	static const std::string gangPath;

	//generate a single strategy
	static void generateStrategy(int pathIndex, const bool gangStrategy);

	//generate a PSIL if statement
	static std::string generateIf(const int currentLineNum, const int totalLines, const bool gangStrategy);
	static std::string intToString(const int x);

	static const int INT_VAR_MIN = -200;
	static const int INT_VAR_MAX = 200;
};

