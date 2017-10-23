#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <random>

#include "PsilLang.h"
#include "prisoner.h"

class Interpreter
{
public:
	//Determine a decison (betray/silent) based on the prisoner's strategy
	static int interpretDecision(Prisoner* prisoner);

private:
	static int processLine(Prisoner* prisoner, const int lineNumber);
	static int parseIf(Prisoner* prisoner, const int lineNumber, const std::vector<std::string>& tokens);
};

