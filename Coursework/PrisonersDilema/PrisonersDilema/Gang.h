#pragma once

#include "GangMember.h"

class Gang
{
public:
	Gang();
	Gang(const int id, const std::vector<GangMember*>& prisoners);
	~Gang();

	static const int GANG_SIZE = 5;

	inline const std::vector<GangMember*>& getMembers() const { return mGangMembers; }
	inline const GangMember* getMember(const int i) const { return mGangMembers[i]; }
	inline const std::string& getName() const { return mName; }
	inline const int getVariable(const int n) const { return mVariables[n]; }
	inline const float getScore() const { return mScore; }
	inline const float getCumulativeScore() const { return mCumulativeScore; }

	friend std::ostream& operator<<(std::ostream& os, const Gang* g);

	//Reset all but CUMULATIVE_SCORE
	void softReset();
	//Reset all including CUMULATIVE_SCORE
	void hardReset();
	//Add current score to cumulative score
	void addScore();

	void incrementIterations();

	void outcomeW();
	void outcomeX();
	void outcomeY();
	void outcomeZ();
	void outcomeA();
	void outcomeB();
	void outcomeC();

private:
	std::string mName;
	std::vector<GangMember*> mGangMembers;

	int mVariables[PsilLang::varEnums::NUM_VARS] = { 0 };
	float mScore = 0.0f;
	float mCumulativeScore = 0.0f;
};