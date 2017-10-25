#pragma once

#include "GangMember.h"

class Gang
{
public:
	Gang();
	Gang(const std::string& id, const std::vector<GangMember*>& prisoners);
	~Gang();

	static const int GANG_SIZE = 5;

	inline const std::vector<GangMember*>& getMembers() const { return mGangMembers; }
	inline const GangMember* getMember(const int i) const { return mGangMembers[i]; }
	inline const std::string& getID() const { return mID; }
	inline const int getVariable(const int n) const { return mVariables[n]; }

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
	std::string mID;
	std::vector<GangMember*> mGangMembers;

	int mVariables[PsilLang::varEnums::NUM_VARS] = { 0 };
};