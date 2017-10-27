#pragma once

#include "Prisoner.h"

class GangMember : public Prisoner
{
public:
	GangMember();
	GangMember(Prisoner* p);
	GangMember(GangMember* gm);
	~GangMember();

	inline const float getScore() const { return mScore; }
	virtual inline void addToScore(const float x) { mScore += x; }
	inline const float getCumulativeScore() const { return mCScore; }

	inline const bool getSpy() const { return mIsSpy; }
	inline void setSpy(const bool spy) { mIsSpy = spy; }

	inline const bool getLeader() const { return mIsSpy; }
	inline void setLeader(const bool leader) { mIsSpy = leader; }

	virtual void outcomeW(const bool updated);
	virtual void outcomeX(const bool updated);
	virtual void outcomeY(const bool updated);
	virtual void outcomeZ(const bool updated);
	virtual void outcomeA(const bool updated);
	virtual void outcomeB(const bool updated);
	virtual void outcomeC(const bool updated);

	//Reset all but CUMULATIVE_SCORE
	void softReset();
	//Reset all including CUMULATIVE_SCORE
	void hardReset();
	//Add current score to cumulative score
	inline void addScore() { mCScore += mScore; }

	friend std::ostream& operator<<(std::ostream& os, const GangMember* gm);

private:
	float mScore = 0.0f;
	float mCScore = 0.0f;

	bool mIsSpy;
	bool mIsLeader;
};

