#pragma once

#include "Game.h"
#include "Gang.h"

class GangGame
{
public:
	GangGame();
	GangGame(Gang* a, Gang* b, int spyChance);
	~GangGame();

	//Plays a game of n iterations between two prisoner strategies
	virtual void play(const int gameNum, int n = 200);
private:
	void updateVariables(const int decisionsA[], const int decisionsB[]);
	//Determine whether or not to add a spy to the gang
	void addSpy(Gang* g);

	Gang* mGangA;
	Gang* mGangB;
	int mSpyChance;
};

