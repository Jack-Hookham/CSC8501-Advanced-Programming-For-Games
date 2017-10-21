#include "TIPDPGame.h"

TIPDPGame::TIPDPGame(Prisoner* a, Prisoner* b)
{
	mPrisonerA = a;
	mPrisonerB = b;
}

TIPDPGame::~TIPDPGame()
{
}

void TIPDPGame::play(const int n)
{
	for (int i = 0; i < n; i++)
	{
		int decisionA = Interpreter::interpretDecision(mPrisonerA);
		//Friend? compare prisoner strategies

		int decisionB = Interpreter::interpretDecision(mPrisonerB);

		updateVariables(decisionA, decisionB);
	}
}

void TIPDPGame::updateVariables(const int decisionA, const int decisionB)
{
	mPrisonerA->incrementIterations();

}
