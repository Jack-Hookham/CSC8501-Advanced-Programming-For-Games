#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <ctime>

#include "FileManager.h"
#include "Globals.h"
#include "Language.h"

class StrategyGenerator
{
public:
	//generate n random strategies
	static void generate(int n);

private:
	//generate a single strategy
	static void generateStrategy(int index);

	//generate a PSIL if statement
	static std::string generateIf();
};

