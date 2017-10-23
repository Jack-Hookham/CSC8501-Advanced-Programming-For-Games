#pragma once

#include "prisoner.h"
#include "Interpreter.h"

//The Iterated Prisoners Dilemma Problem Game between two prisoners

class Game
{
public:
	Game();
	Game(Prisoner* a, Prisoner* b);
	~Game();

	//Plays a game of n iterations between to prisoner strategies
	void play(const int gameNum, int n = 200);

private:
	void updateVariables(const int decisionA, const int decisionB);

	Prisoner* mPrisonerA;
	Prisoner* mPrisonerB;
};

