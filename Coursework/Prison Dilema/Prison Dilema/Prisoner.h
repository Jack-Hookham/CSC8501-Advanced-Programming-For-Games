#pragma once

#include <iostream>
#include <vector>

#include "FileManager.h"
#include "Language.h"

class Prisoner
{

public:
	Prisoner();
	//Reads a strategy from file and adds each line to the strategy array
	Prisoner(std::string filePath);
	~Prisoner();

	enum decisions
	{
		BETRAY,
		SILENT,
		INVALID_FILE
	};

	inline std::string getStrategy() { return strategy[Language::MAX_READ_LINES]; }
	inline std::string getStrategyLine(int i) { return strategy[i]; }
	void setStrategy(std::string filePath);

	//Game variable getters
	inline std::string getLastOutcome() { return lastOutcome; }
	inline std::string getCurrentOutcome() { return currentOutcome; }
	inline int getAllOutcomes_w() { return allOutcomes_w; }
	inline int getAllOutcomes_x() { return allOutcomes_x; }
	inline int getAllOutcomes_y() { return allOutcomes_y; }
	inline int getAllOutcomes_z() { return allOutcomes_z; }
	inline int getIterations() { return iterations; }
	inline int getMyScore() { return myScore; }

	//Game variable setters
	inline void setLastOutcome(std::string outcome) { lastOutcome = outcome; }
	inline void setCurrentOutcome(std::string outcome) { currentOutcome = outcome; }
	inline void setAllOutComes_w(int outcomes) { allOutcomes_w = outcomes; }
	inline void setAllOutComes_x(int outcomes) { allOutcomes_x = outcomes; }
	inline void setAllOutComes_y(int outcomes) { allOutcomes_y = outcomes; }
	inline void setAllOutComes_z(int outcomes) { allOutcomes_z = outcomes; }

	void print();

private:
	//Array of strings containing the strategy
	std::string strategy[Language::MAX_READ_LINES];

	//Game variables
	std::string lastOutcome;
	std::string currentOutcome;
	int allOutcomes_w = 0;
	int allOutcomes_x = 0;
	int allOutcomes_y = 0;
	int allOutcomes_z = 0;
	int iterations = 0;
	int myScore = 0;

	template<size_t size, class T>
	inline int arraySize(T(&arr)[size])
	{
		return size;
	}
};

