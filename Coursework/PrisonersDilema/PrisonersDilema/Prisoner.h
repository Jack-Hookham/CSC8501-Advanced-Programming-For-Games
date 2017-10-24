#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

#include "FileManager.h"
#include "PsilLang.h"

class Prisoner
{

public:
	Prisoner();
	Prisoner(Prisoner* prisoner);
	//Reads a strategy from file and adds each line to the strategy map
	Prisoner(const std::string& const folderPath);
	~Prisoner();

	enum decisions
	{
		BETRAY,
		SILENCE,
		INVALID_FILE
	};

	inline const std::map<int, std::string>& getStrategy() const { return mStrategy; }
	inline const std::string& getStrategyLine(const int n) const { return mStrategy.at(n); }
	inline const int getVariable(const int n) const { return mVariables[n]; }
	inline const std::string& getStrategyName() const { return mStrategyName; }
	inline const std::string& getStrategyPath() const { return mStrategyPath; }

	void setStrategy(const std::string& const filePath);
	inline void setVariable(const int n, const int value) { mVariables[n] = value; }

	inline void incrementIterations() { mVariables[PsilLang::varEnums::ITERATIONS]++; }
	
	void outcomeW();
	void outcomeX();
	void outcomeY();
	void outcomeZ();

	void printStrategy();

	friend std::ostream& operator<<(std::ostream& os, const Prisoner* p);

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

	int mVariables[PsilLang::varEnums::NUM_VARS] = { 0 };
};

