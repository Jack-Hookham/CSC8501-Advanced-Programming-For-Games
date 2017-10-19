#include "TIPDPGame.h"

TIPDPGame::TIPDPGame(Prisoner& a, Prisoner& b)
{
	this->a = a;
	this->b = b;
}

TIPDPGame::~TIPDPGame()
{
}

void TIPDPGame::play(int n)
{
	for (int i = 0; i < n; i++)
	{
		int currentOutcomeA = Interpreter::compareStrategies(a, b);

		int currentOutcomeB;
	}


}
