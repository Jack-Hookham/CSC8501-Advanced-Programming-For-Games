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
	static void generate(const int n, const bool gangStrategy = false, const int lineNumIncrement = 1);

private:
	static const std::string prisonerPath;
	static const std::string gangPath;

	//generate a single strategy
	static void generateStrategy(int pathIndex, const bool gangStrategy, const int lineNumIncrement);

	//generate a PSIL if statement
	static std::string generateIf(const int currentLineNum, const int lineNumIncrementconst, int totalLines, const bool gangStrategy);
	static void generateVars(std::vector<int>& lhsVars, std::vector<int>& rhsVars, const bool gangStrategy);
	static const int generateOperators(std::vector<int>& lhsOps, std::vector<int>& rhsOps);
	static std::string intToString(const int x);

	static const int INT_VAR_MIN = -200;
	static const int INT_VAR_MAX = 200;
};

