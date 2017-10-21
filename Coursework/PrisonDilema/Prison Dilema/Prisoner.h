#pragma once

#include <iostream>
#include <vector>
#include<map>

#include "FileManager.h"
#include "PsilLang.h"

class Prisoner
{

public:
	Prisoner();
	//Reads a strategy from file and adds each line to the strategy map
	Prisoner(std::string filePath);
	~Prisoner();

	enum decisions
	{
		BETRAY,
		SILENCE,
		INVALID_FILE
	};

	//enum gameVariablesEnums
	//{
	//	ALL_OUTCOMES_W,
	//	ALL_OUTCOMES_X,
	//	ALL_OUTCOMES_Y,
	//	ALL_OUTCOMES_Z,
	//	ITERATIONS,
	//	MY_SCORE,
	//	NUM_VARIABLES
	//};

	inline std::map<int, std::string>& getStrategy() { return mStrategy; }
	inline std::string getStrategyLine(int n) { return mStrategy.at(n); }
	void setStrategy(std::string filePath);

	//Game variable getters
	//inline std::string getLastOutcome() { return lastOutcome; }
	//inline std::string getCurrentOutcome() { return currentOutcome; }
	//inline int getAllOutcomes_w() { return allOutcomes_w; }
	//inline int getAllOutcomes_x() { return allOutcomes_x; }
	//inline int getAllOutcomes_y() { return allOutcomes_y; }
	//inline int getAllOutcomes_z() { return allOutcomes_z; }
	//inline int getIterations() { return iterations; }
	//inline int getMyScore() { return myScore; }

	inline int getVariable(const int n) const { return mVariables[n]; }

	//Game variable setters
	//inline void setLastOutcome(std::string outcome) { lastOutcome = outcome; }
	//inline void setCurrentOutcome(std::string outcome) { currentOutcome = outcome; }
	//inline void setAllOutComes_w(int outcomes) { allOutcomes_w = outcomes; }
	//inline void setAllOutComes_x(int outcomes) { allOutcomes_x = outcomes; }
	//inline void setAllOutComes_y(int outcomes) { allOutcomes_y = outcomes; }
	//inline void setAllOutComes_z(int outcomes) { allOutcomes_z = outcomes; }

	inline void setVariable(const int n, const int value) { mVariables[n] = value; }
	inline void incrementIterations() { mVariables[PsilLang::psilVars[PsilLang::varEnums::ITERATIONS]]++; }

	void print();

private:
	//Array of strings containing the strategy
	std::map<int, std::string> mStrategy;

	int mVariables[PsilLang::varEnums::NUM_VARIABLES] = { 0 };
};

