#include "GangGame.h"

GangGame::GangGame()
{
}

GangGame::GangGame(Gang* a, Gang* b)
{
}

GangGame::~GangGame()
{
}

void GangGame::play(const int gameNum, int n)
{
	//Play n games
	for (int i = 0; i < n; i++)
	{
		std::vector<int> decisionsA;
		std::vector<int> decisionsB;

		//Get a decision for every prisoner in both gangs
		for (int j = 0; j < GANG_SIZE; j++)
		{
			decisionsA.push_back(Interpreter::interpretDecision(mGangA->getPrisoner(j)));
			decisionsB.push_back(Interpreter::interpretDecision(mGangA->getPrisoner(j)));

			if (decisionsA[j] == Prisoner::INVALID_FILE || decisionsB[j] == Prisoner::INVALID_FILE)
			{
				std::cout << "Invalid file! Game aborted.\n";

				mGangA->softReset();
				mGangB->softReset();

				return;
			}

			updateVariables(decisionsA, decisionsB);
		}

	}
	std::cout << "\nGame " << mGamesPlayed << "\n";
	//Print the variables for both prisoners at the end of the game
	std::cout << mGangA;
	std::cout << mGangB;

	//Add scores to cumulative scores
	mGangA->addScore();
	mGangB->addScore();

	//Reset the variables after the game
	mGangA->softReset();
	mGangB->softReset();
}

void GangGame::updateVariables(const std::vector<int>& decisionsA, const std::vector<int>& decisionsB)
{

}
