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
	void updateVariables(const std::vector<int>& decisionsA, const std::vector<int>& decisionsB);

	Gang* mGangA;
	Gang* mGangB;	
	
	//Track the total number of games played
	int mGamesPlayed = 0;
	const int GANG_SIZE = 5;
};

