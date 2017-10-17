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
		NUM_OPERATORS
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
		NUM_VARS
	};

	static const std::string psil_keywords[];
	static const std::string psil_operators[];
	static const std::string psil_vars[];

	static const int MAXLINES = 15;
};

