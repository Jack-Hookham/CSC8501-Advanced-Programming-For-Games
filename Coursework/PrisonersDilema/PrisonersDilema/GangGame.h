#pragma once

#include "Game.h"
#include "Gang.h"

class GangGame
{
public:
	GangGame();
	GangGame(Gang* a, Gang* b);
	~GangGame();

	//Plays a game of n iterations between two prisoner strategies
	virtual void play(const int gameNum, int n = 200);
private:
	void updateVariables(const int decisionsA[], const int decisionsB[]);

	Gang* mGangA;
	Gang* mGangB;
};

