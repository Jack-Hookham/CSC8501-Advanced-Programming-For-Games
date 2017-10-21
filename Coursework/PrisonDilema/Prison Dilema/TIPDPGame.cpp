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
	mPrisonerB->incrementIterations();

	if (decisionA == decisionB == Prisoner::decisions::SILENCE)
	{
		mPrisonerA->outcomeW();
		mPrisonerB->outcomeW();
	}
	else if (decisionA == Prisoner::decisions::SILENCE && decisionB == Prisoner::decisions::BETRAY)
	{
		mPrisonerA->outcomeX();
		mPrisonerB->outcomeY();
	}
	else if (decisionA == Prisoner::decisions::BETRAY && decisionB == Prisoner::decisions::SILENCE)
	{
		mPrisonerA->outcomeY();
		mPrisonerB->outcomeX();
	}
	else if (decisionA == decisionB == Prisoner::decisions::BETRAY)
	{
		//Update variables for both prisoners
		mPrisonerA->outcomeZ();
		mPrisonerB->outcomeZ();
	}
	else
	{
		//ERROR
	}
}
