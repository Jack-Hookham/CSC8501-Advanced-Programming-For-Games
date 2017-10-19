#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <regex>

#include "Language.h"
#include "Prisoner.h"

class Interpreter
{
public:
	//Determine a decison (betray/silent) based on the prisoner's strategy
	static int interpretDecision(Prisoner& prisoner);

	//Compare two strategies and determine a result for strategyA
	static int compareStrategies(Prisoner& prisonerA, Prisoner& prisonerB);

private:
	static bool isInteger(const std::string& s)
	{
		return std::regex_match(s, std::regex("^([+-]?[0-9]\d*|0)$"));
	}
};

