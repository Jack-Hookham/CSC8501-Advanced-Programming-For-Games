#include "Tournament.h"

Tournament::Tournament()
{
}

Tournament::Tournament(const int id, const std::vector<std::string>& strategies, const int gameIterations, const int tournamentIterations)
{
	mID = id;
	mNumStrategies = strategies.size();
	mGameIterations = gameIterations;
	mTournamentIterations = tournamentIterations;

	generatePrisoners(strategies);
}

Tournament::~Tournament()
{
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		delete mPrisoners[i];
	}
	mPrisoners.clear();
}

void Tournament::generatePrisoners(const std::vector<std::string>& strategies)
{
	//Create a Prisoner for each strategy
	for (int i = 0; i < strategies.size(); i++)
	{
		mPrisoners.push_back(new Prisoner(strategies[i]));
	}
}

void Tournament::play()
{
	std::cout << lineBreak;
	std::cout << std::setw(15) << "\nStrategy Name";
	
	for (int i = 0; i <= PsilLang::varEnums::ALLOUTCOMES_Z; i++)
	{
		std::cout << std::setw(PsilLang::psilVars[i].length() + 2) << PsilLang::psilVars[i];
	}
	std::cout << "\n";
	std::cout << lineBreak;

	int gameNum = 1;
	for (int i = 0; i < mTournamentIterations; i++)
	{
		for (int i = 0; i < mPrisoners.size(); i++)
		{
			for (int j = i + 1; j < mPrisoners.size(); j++)
			{
				mGamesPlayed++;
				Game* game = new Game(mPrisoners[i], mPrisoners[j]);
				game->play(mGamesPlayed, mGameIterations);
				gameNum++;
				delete game;
			}
		}
	}
}

void Tournament::generateResults()
{
	std::ostringstream ossResults;
	ossResults << lineBreak;
	ossResults << "\nNumber of Strategies: " << mNumStrategies << "   Tournament Iterations: " << mTournamentIterations << "   Game Iterations: " << mGameIterations << "\n\n";
	ossResults << std::left << std::setw(15) << "Strategy Name" << "Total Score" << "\n\n";

	int winner = 0;
	//Print each prisoner's cumulative score and determine a winner (lowest score)
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		ossResults << std::left << std::setw(15) << mPrisoners[i]->getStrategyName() << mPrisoners[i]->getVariable(PsilLang::varEnums::CUMULATIVE_SCORE) << "\n";

		if (mPrisoners[i]->getVariable(PsilLang::varEnums::CUMULATIVE_SCORE) < mPrisoners[winner]->getVariable(PsilLang::varEnums::CUMULATIVE_SCORE))
		{
			winner = i;
		}
	}
	ossResults << lineBreak;
	ossResults << "\nWinning strategy: " << mPrisoners[winner]->getStrategyName() << "\n";
	ossResults << lineBreak;

	mTournamentResults = ossResults.str();
	std::ostringstream path;
	path << resultsPath << "TournamentResults" << mID << ".txt";
	FileManager::writeToFile(path.str(), mTournamentResults);
	std::cout << this;
}
