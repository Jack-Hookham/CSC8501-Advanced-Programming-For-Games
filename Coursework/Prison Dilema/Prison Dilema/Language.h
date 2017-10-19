#pragma once

#include <iostream>
#include <regex>

class Language
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
		W,
		X,
		Y,
		Z
	};

	static const std::string psil_keywords[];
	static const std::string psil_operators[];
	static const std::string psil_vars[];

	//Maximum lines that can be written to a strategy file
	static const int MAX_WRITE_LINES = 15;
	
	//Maximum lines that can be read from a strategy file
	static const int MAX_READ_LINES = 50;

	//inline static bool isInteger(const std::string& s) { return std::regex_match(s, std::regex("^([+-]?[0-9]\d*|0)$")); }
	inline static bool isInteger(const std::string& s) { return s.find_first_not_of("0123456789") == std::string::npos; }
};

