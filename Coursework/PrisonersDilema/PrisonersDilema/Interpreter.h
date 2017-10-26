#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <random>

#include "PsiLang.h"
#include "prisoner.h"

class Interpreter
{
public:
	//Determine a decison (betray/silent) based on the prisoner's strategy
	static int interpretDecision(const Prisoner* prisoner);

private:
	//lineNumber = the line identifier used in the strategy file
	//lineIndex = the actual line number incrementing by 1 for each line - used to ensure the strategy file isn't too long
	static int processLine(const Prisoner* prisoner, const int lineNumber, const int lineIndex = 1);
	static int parseIf(const Prisoner* prisoner, const int lineNumber, const std::vector<std::string>& tokens);
};

