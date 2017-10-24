#include "GangGame.h"

GangGame::GangGame()
{
}

GangGame::GangGame(Gang* a, Gang* b)
{
	mGangA = a;
	mGangB = b;
}

GangGame::~GangGame()
{
}

void GangGame::play(const int gamesPlayed, int gameIterations)
{
	//Play n games
	for (int i = 0; i < gameIterations; i++)
	{
		std::vector<int> decisionsA;
		std::vector<int> decisionsB;

		//Get a decision for every prisoner in both gangs
		for (int j = 0; j < GANG_SIZE; j++)
		{
			decisionsA.push_back(Interpreter::interpretDecision(mGangA->getPrisoner(j)));
			decisionsB.push_back(Interpreter::interpretDecision(mGangB->getPrisoner(j)));

			if (decisionsA[j] == Prisoner::decisions::INVALID_FILE || decisionsB[j] == Prisoner::decisions::INVALID_FILE)
			{
				std::cout << "Invalid file! Game aborted.\n";

				mGangA->softReset();
				mGangB->softReset();

				return;
			}
		}
		updateVariables(decisionsA, decisionsB);

		std::cout << mGangA;
		std::cout << mGangB;
	}
	std::cout << "\nGame " << gamesPlayed << "\n";
	//Print the variables for both gangs at the end of the game
	//std::cout << mGangA;
	//std::cout << mGangB;

	//Add scores to cumulative scores
	mGangA->addScore();
	mGangB->addScore();

	//Reset the variables after the game
	mGangA->softReset();
	mGangB->softReset();
}

void GangGame::updateVariables(const std::vector<int>& decisionsA, const std::vector<int>& decisionsB)
{
	mGangA->incrementIterations();
	mGangB->incrementIterations();

	//+1 for silence, -1 for betray
	int silenceCountA = 0;
	int silenceCountB = 0;

	//Adjust decision counters based on gang member decisions
	for (int i = 0; i < GANG_SIZE; i++)
	{
		if (decisionsA[i] == Prisoner::decisions::SILENCE) { silenceCountA++; }
		else { silenceCountA--; }

		if (decisionsB[i] == Prisoner::decisions::SILENCE){ silenceCountB++; }
		else{ silenceCountB--; }
	}

	int gangDecisionA;
	int gangDecisionB;

	//Determine gang decisions based on prisoner decisions
	if (silenceCountA < 0) { gangDecisionA = Prisoner::decisions::BETRAY; }
	else if (silenceCountA > 0) { gangDecisionA = Prisoner::decisions::SILENCE; }
	else { std::cout << "Something went wrong! Number of betray decisions same as number of silence decisions!"; }

	if (silenceCountB < 0) { gangDecisionB = Prisoner::decisions::BETRAY; }
	else if (silenceCountB > 0) { gangDecisionB = Prisoner::decisions::SILENCE; }
	else { std::cout << "Something went wrong! Number of betray decisions same as number of silence decisions!"; }

	if (gangDecisionA == Prisoner::decisions::SILENCE && gangDecisionB == Prisoner::decisions::SILENCE)
	{
		mGangA->outcomeW();
		mGangB->outcomeW();
	}
	else if (gangDecisionA == Prisoner::decisions::SILENCE && gangDecisionB == Prisoner::decisions::BETRAY)
	{
		mGangA->outcomeX();
		mGangB->outcomeY();
	}
	else if (gangDecisionA == Prisoner::decisions::BETRAY && gangDecisionB == Prisoner::decisions::SILENCE)
	{
		mGangA->outcomeY();
		mGangB->outcomeX();
	}
	else if (gangDecisionA == Prisoner::decisions::BETRAY && gangDecisionB == Prisoner::decisions::BETRAY)
	{
		mGangA->outcomeZ();
		mGangB->outcomeZ();
	}
	else
	{
		//ERROR
	}

	//A had more betrays
	if (silenceCountA < silenceCountB)
	{
		mGangA->outcomeA();
		mGangB->outcomeB();
	}
	//B had more betrays
	else if (silenceCountA > silenceCountB)
	{
		mGangA->outcomeB();
		mGangB->outcomeA();
	}
	//Same number of betrays
	else
	{
		mGangA->outcomeC();
		mGangB->outcomeC();
	}
}
