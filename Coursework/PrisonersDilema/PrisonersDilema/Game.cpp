#include "Game.h"

Game::Game()
{
}

Game::Game(Prisoner* a, Prisoner* b)
{
	mPrisonerA = a;
	mPrisonerB = b;
}

Game::~Game()
{
}

void Game::play(const int gamesPlayed, const int n)
{
	for (int i = 0; i < n; i++)
	{
		int decisionA = Interpreter::interpretDecision(mPrisonerA);
		int decisionB = Interpreter::interpretDecision(mPrisonerB);

		if (decisionA == Prisoner::INVALID_FILE || decisionB == Prisoner::INVALID_FILE)
		{
			std::cout << "Invalid file! Game aborted.\n";

			mPrisonerA->softReset();
			mPrisonerB->softReset();

			return;
		}

		updateVariables(decisionA, decisionB);
	}

	std::cout << "\nGame " << gamesPlayed << "\n";
	//Print the variables for both prisoners at the end of the game
	std::cout << mPrisonerA; 
	std::cout << mPrisonerB;

	//Add scores to cumulative scores
	mPrisonerA->addScore();
	mPrisonerB->addScore();

	//Reset the variables after the game
	mPrisonerA->softReset();
	mPrisonerB->softReset();
}

//Update variables for both prisoners
void Game::updateVariables(const int decisionA, const int decisionB)
{
	mPrisonerA->incrementIterations();
	mPrisonerB->incrementIterations();

	if (decisionA == Prisoner::decisions::SILENCE && decisionB == Prisoner::decisions::SILENCE)
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
	else if (decisionA == Prisoner::decisions::BETRAY && decisionB == Prisoner::decisions::BETRAY)
	{
		mPrisonerA->outcomeZ();
		mPrisonerB->outcomeZ();
	}
	else
	{
		//ERROR
	}
}
