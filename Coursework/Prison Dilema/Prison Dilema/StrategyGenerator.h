#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include "FileManager.h"

class StrategyGenerator
{
public:
	//generate n random strategies
	static void generate(int n);

private:
	//generate a single strategy
	static void generateStrategy(int index);
};

