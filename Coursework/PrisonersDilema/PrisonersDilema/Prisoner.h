#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "FileManager.h"
#include "PsilLang.h"

class Prisoner
{

public:
	Prisoner();
	//Reads a strategy from file and adds each line to the strategy map
	Prisoner(const std::string folderPath);
	~Prisoner();

	enum decisions
	{
		BETRAY,
		SILENCE,
		INVALID_FILE
	};

	inline const std::map<int, std::string>& getStrategy() const { return mStrategy; }
	inline const std::string getStrategyLine(const int n) const { return mStrategy.at(n); }
	void setStrategy(const std::string filePath);

	inline const int getVariable(const int n) const { return mVariables[n]; }
	inline const std::string getStrategyName() const { return mStrategyName; }

	inline void setVariable(const int n, const int value) { mVariables[n] = value; }
	inline void incrementIterations() { mVariables[PsilLang::varEnums::ITERATIONS]++; }
	
	void outcomeW();
	void outcomeX();
	void outcomeY();
	void outcomeZ();

	void printStrategy();
	void printVariables();
	//Reset all but CUMULATIVE_SCORE
	void softReset();
	//Reset all including CUMULATIVE_SCORE
	void hardReset();
	//Add current score to cumulative score
	inline void addScore() { mVariables[PsilLang::varEnums::CUMULATIVE_SCORE] += mVariables[PsilLang::varEnums::MYSCORE]; }

private:
	std::string mStrategyName;
	std::string mStrategyPath;

	//Map of strings containing the strategy
	//Key = line number, value = strategy string
	std::map<int, std::string> mStrategy;

	int mVariables[PsilLang::varEnums::CUMULATIVE_SCORE + 1] = { 0 };
};

