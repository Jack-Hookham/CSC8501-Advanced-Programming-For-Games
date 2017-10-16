#pragma once

#include <iostream>

class Interpreter
{
public:
	Interpreter();
	~Interpreter();

private:
	const std::string KEYWORDS[5] = { "IF", "GOTO", "BETRAY", "SILENCE", "RANDOM" };
	const char OPERATORS[5] = { '+', '-', '>', '<', '=' };
	const std::string VARIABLES[7] = { "LASTOUTCOME", "ALLOUTCOMES_W", "ALLOUTCOMES_X", "ALLOUTCOMES_Y", "ALLOUTCOMES_Z", "ITERATIONS", "MYSCORE" };
};

