#include "IPDPGame.h"

IPDPGame::IPDPGame(Prisoner* a, Prisoner* b)
{
	mPrisonerA = a;
	mPrisonerB = b;
}

IPDPGame::~IPDPGame()
{
}

void IPDPGame::play(const int n)
{
	for (int i = 0; i < n; i++)
	{
		int decisionA = Interpreter::interpretDecision(mPrisonerA);
		//Friend? compare prisoner strategies

		int decisionB = Interpreter::interpretDecision(mPrisonerB);

		updateVariables(decisionA, decisionB);

		//mPrisonerA->printVariables();
		//mPrisonerB->printVariables();
	}
	std::cout << "\n";

	//Print the variables for both prisoners at the end of the game
	mPrisonerA->printVariables();
	mPrisonerB->printVariables();

	//Add scores to cumulative scores
	mPrisonerA->addScore();
	mPrisonerB->addScore();

	//Reset the variables after the game
	mPrisonerA->softReset();
	mPrisonerB->softReset();
}

//Update variables for both prisoners
void IPDPGame::updateVariables(const int decisionA, const int decisionB)
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
		mPrisonerA->outcomeZ();
		mPrisonerB->outcomeZ();
	}
	else
	{
		//ERROR
	}
}
