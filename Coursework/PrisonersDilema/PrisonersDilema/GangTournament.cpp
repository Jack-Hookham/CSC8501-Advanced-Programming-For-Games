#include "GangTournament.h"

GangTournament::GangTournament()
{
}

GangTournament::GangTournament(const int id, const std::vector<std::string>& strategies, const int gameIterations, const int tournamentIterations, const int numGangs)
{
	mID = id;
	mNumStrategies = strategies.size();
	mGameIterations = gameIterations;
	mTournamentIterations = tournamentIterations;

	generatePrisoners(strategies);
	//Randomly populate each gang with new prisoners
	//Each prisoner uses one of the strategies provided
	for (int i = 0; i < numGangs; i++)
	{
		std::vector<Prisoner*> prisoners;
		for (int i = 0; i < 5; i++)
		{
			int prisonerID = RandomGen::generateRandomWithinRange(0, mPrisoners.size() - 1);
			prisoners.push_back(new Prisoner(mPrisoners[prisonerID]));
		}
		mGangs.push_back(new Gang(i + 1, prisoners));
	}

	for (int i = 0; i < mGangs.size(); i++)
	{
		std::cout << mGangs[i];
	}
}

GangTournament::~GangTournament()
{
	Tournament::~Tournament();
	for (int i = 0; i < mGangs.size(); i++)
	{
		delete mGangs[i];
	}
	mGangs.clear();
}

void GangTournament::play()
{
	printTournamentHeading();

	for (int i = 0; i < mTournamentIterations; i++)
	{
		for (int j = 0; j < mGangs.size(); j++)
		{
			for (int k = j + 1; k < mGangs.size(); k++)
			{
				mGamesPlayed++;
				GangGame* game = new GangGame(mGangs[j], mGangs[k]);
				game->play(mGamesPlayed, mGameIterations);
				delete game;
			}
		}
	}
}

void GangTournament::generateResults()
{
}
