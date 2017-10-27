#pragma once

#include <iostream>
#include <regex>
#include <map>

class PsiLang
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
		ITERATIONS,
		MYSCORE,
		ALLOUTCOMES_W,			
		ALLOUTCOMES_X,			
		ALLOUTCOMES_Y,			
		ALLOUTCOMES_Z,			
		INTEGER_PLACEHOLDER_1,	//used in strategy generation - if this value is generated in an if statement it will be replaced by a random integer
		ALLOUTCOMES_A,			
		ALLOUTCOMES_B,			
		ALLOUTCOMES_C,			
		INTEGER_PLACEHOLDER_2,
		W,						//Both silent
		X,						//Self silent, other betray
		Y,						//Self betray, other silent
		Z,						//Both betray
		A,						//Mixed response, most betrays
		B,						//Mixed response, least betrays
		C,						//Mixed response, both gangs same cumulative decision
		UNKOWN_DECISION,		//Unknown decision - decisions will be initialised with this
		CUMULATIVE_SCORE,		
		NUM_VARS
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

