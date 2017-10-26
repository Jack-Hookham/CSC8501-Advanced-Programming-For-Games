#pragma once

#include "GangMember.h"

class Gang// : public GangMember
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
	inline const float getCumulativeScore() const { return mCScore; }
	inline const int getTotalSpies() const { return mTotalSpies; }
	inline const int getDiscoveredSpies() const { return mDiscoveredSpies; }
	inline const int getCTotalSpies() const { return mCTotalSpies; }
	inline const int getCDiscoveredSpies() const { return mCDiscoveredSpies; }
	inline const int getDiscoveredPercent() const { return mDiscoveredPercent; }

	inline void setDiscoveredPercent(const float value) { mDiscoveredPercent = value; }

	friend std::ostream& operator<<(std::ostream& os, const Gang* g);

	void addToScore(const float x);

	//Reset all but CUMULATIVE_SCORE
	void softReset();
	//Reset all including CUMULATIVE_SCORE
	void hardReset();
	//Add current score to cumulative score and total spies and discovered spies to cumulative values
	void addScore();

	void incrementIterations();
	inline void incrementTotalSpies() { mTotalSpies++; }
	inline void incrementDiscoveredSpies() { mDiscoveredSpies++; }

	void outcomeW(const bool updated);
	void outcomeX(const bool updated);
	void outcomeY(const bool updated);
	void outcomeZ(const bool updated);
	void outcomeA(const bool updated);
	void outcomeB(const bool updated);
	void outcomeC(const bool updated);

	void setSpy(const int index);
	//Set spy values of all members to false
	void removeSpies();
private:
	std::string mName;
	std::vector<GangMember*> mGangMembers;
	int mTotalSpies = 0;
	int mDiscoveredSpies = 0;
	int mCTotalSpies = 0;
	int mCDiscoveredSpies = 0;
	float mDiscoveredPercent = 0.0f;

	int mVariables[PsiLang::varEnums::NUM_VARS] = { 0 };
	float mScore = 0.0f;
	float mCScore = 0.0f;
};