#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <random>

#include "Language.h"
#include "Prisoner.h"

class Interpreter
{
public:
	//Determine a decison (betray/silent) based on the prisoner's strategy
	static int interpretDecision(Prisoner& prisoner);

private:
	static int processStrategy();
	static int processLine(const std::string line);
	static int parseIf(const std::vector<std::string>& tokens);
};

