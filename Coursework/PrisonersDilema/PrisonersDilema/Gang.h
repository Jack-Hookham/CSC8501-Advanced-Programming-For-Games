#pragma once

#include "Prisoner.h"

class Gang
{
public:
	Gang();
	Gang(int id, std::vector<Prisoner*> prisoners);
	~Gang();

	inline const std::vector<Prisoner*>& getPrisoners() const { return mPrisoners; }
	inline const Prisoner* getPrisoner(const int i) const { return mPrisoners[i]; }
	inline const int getID() const { return mID; }
	inline const int getVariable(const int n) const { return mVariables[n]; }

	friend std::ostream& operator<<(std::ostream& os, const Gang* g);

	//Reset all but CUMULATIVE_SCORE
	void softReset();
	//Reset all including CUMULATIVE_SCORE
	void hardReset();
	//Add current score to cumulative score
	inline void addScore() { mVariables[PsilLang::varEnums::CUMULATIVE_SCORE] += mVariables[PsilLang::varEnums::MYSCORE]; }

	inline void incrementIterations() { mVariables[PsilLang::varEnums::ITERATIONS]++; }

	void outcomeW();
	void outcomeX();
	void outcomeY();
	void outcomeZ();

	void outcomeA();
	void outcomeB();
	void outcomeC();

private:
	int mID;
	std::vector<Prisoner*> mPrisoners;

	int mVariables[PsilLang::varEnums::NUM_VARS] = { 0 };
};