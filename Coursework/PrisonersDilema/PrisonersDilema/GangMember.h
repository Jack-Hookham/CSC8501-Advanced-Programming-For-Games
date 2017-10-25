#pragma once

#include "Prisoner.h"

class GangMember : public Prisoner
{
public:
	GangMember();
	GangMember(Prisoner* p);
	GangMember(GangMember* gm);
	GangMember(const std::string& const folderPath);
	~GangMember();

	inline const float getScore() const { return mScore; }
	inline const float getCumulativeScore() const { return mCumulativeScore; }

	void outcomeW();
	void outcomeX();
	void outcomeY();
	void outcomeZ();
	void outcomeA();
	void outcomeB();
	void outcomeC();

	//Reset all but CUMULATIVE_SCORE
	void softReset();
	//Reset all including CUMULATIVE_SCORE
	void hardReset();
	//Add current score to cumulative score
	inline void addScore() { mCumulativeScore += mScore; }

	friend std::ostream& operator<<(std::ostream& os, const GangMember* gm);

private:
	float mScore = 0.0f;
	float mCumulativeScore = 0.0f;
};

