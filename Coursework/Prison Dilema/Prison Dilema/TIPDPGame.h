#pragma once

#include "Prisoner.h"

//The Iterated Prisoners Dilemma Problem Game between two prisoners

class TIPDPGame
{
public:
	TIPDPGame(Prisoner& a, Prisoner& b);
	~TIPDPGame();

	//Plays a game of n iterations between to prisoner strategies
	void play(int n);

private:
	Prisoner a = NULL;
	Prisoner b = NULL;


};

