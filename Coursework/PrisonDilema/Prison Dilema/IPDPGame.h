#pragma once

#include "prisoner.h"
#include "Interpreter.h"

//The Iterated Prisoners Dilemma Problem Game between two prisoners

class IPDPGame
{
public:
	IPDPGame(Prisoner* a, Prisoner* b);
	~IPDPGame();

	//Plays a game of n iterations between to prisoner strategies
	void play(int n = 200);

private:
	void updateVariables(const int decisionA, const int decisionB);

	Prisoner* mPrisonerA;
	Prisoner* mPrisonerB;
};

