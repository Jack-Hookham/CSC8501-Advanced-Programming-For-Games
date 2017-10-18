#pragma once

#include <iostream>

class Language
{
public:
	static enum keywordEnums
	{
		IF,
		GOTO,
		BETRAY,
		SILENCE,
		RANDOM,
		NUM_KEYWORDS
	};

	static enum operatorEnums
	{
		PLUS,
		MINUS,
		GREATER_THAN,
		LESS_THAN,
		EQUALS,
		NO_OP
	};

	static enum varEnums
	{
		LASTOUTCOME,
		ALLOUTCOMES_W,
		ALLOUTCOMES_X,
		ALLOUTCOMES_Y,
		ALLOUTCOMES_Z,
		ITERATIONS,
		MYSCORE,
		NO_VAR
	};

	static const std::string psil_keywords[];
	static const std::string psil_operators[];
	static const std::string psil_vars[];

	//Maximum lines that can be written to a strategy file
	static const int MAX_LINES = 15;
};

