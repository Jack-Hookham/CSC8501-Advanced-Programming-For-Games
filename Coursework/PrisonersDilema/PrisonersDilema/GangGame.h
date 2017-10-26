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
	virtual void play(const int gameNum, const int n = 200, const int gameDetail = 2);
private:
	void updateVariables(const int silenceCountA, const int silenceCountB, const bool scoreUpdated);
	//Determine whether or not to add a spy to the gang
	const int addSpy(Gang* g);
	//Determine whether the leader finds the spy
	const bool findSpy(Gang* g, const int spyIndex, const bool leaderChange);

	Gang* mGangA;
	Gang* mGangB;
	int mSpyChance;
};

