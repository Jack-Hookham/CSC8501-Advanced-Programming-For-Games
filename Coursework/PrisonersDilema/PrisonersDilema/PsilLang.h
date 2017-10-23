#pragma once

#include <iostream>
#include <regex>
#include <map>

class PsilLang
{
public:
	enum keywordEnums
	{
		IF,
		GOTO,
		BETRAY,
		SILENCE,
		RANDOM
	};

	enum operatorEnums
	{
		PLUS,
		MINUS,
		GREATER_THAN,
		LESS_THAN,
		EQUALS
	};

	enum varEnums
	{
		LASTOUTCOME,
		ALLOUTCOMES_W,
		ALLOUTCOMES_X,
		ALLOUTCOMES_Y,
		ALLOUTCOMES_Z,
		ITERATIONS,
		MYSCORE,
		CUMULATIVE_SCORE,
		W,
		X,
		Y,
		Z
	};

	static const std::string psilKeywords[];
	static const std::string psilOperators[];
	static const std::string psilVars[];

	static const std::map<std::string, int> stringToEnumMap;

	//Maximum lines that can be written to a strategy file
	static const int MAX_WRITE_LINES = 15;
	
	//Maximum lines that can be read from a strategy file
	static const int MAX_READ_LINES = 30;

	inline static bool isInteger(const std::string& s) { return s.find_first_not_of("-0123456789") == std::string::npos; }
};

