#pragma once

#include "PSILWord.h"

class Language
{
public:
	static enum keywordsEnum
	{
		IF,
		GOTO,
		BETRAY,
		SILENCE,
		RANDOM,
		PLUS,
		MINUS,
		GREATER_THAN,
		LESS_THAN,
		EQUALS,
		LASTOUTCOME,
		ALLOUTCOMES_W,
		ALLOUTCOMES_X,
		ALLOUTCOMES_Y,
		ALLOUTCOMES_Z,
		ITERATIONS,
		MYSCORE
	};

	static const std::string keywords[];

	static const int MAXLINES = 15;
};

