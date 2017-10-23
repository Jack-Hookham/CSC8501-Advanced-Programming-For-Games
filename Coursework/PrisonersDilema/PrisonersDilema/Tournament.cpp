#include "Tournament.h"

Tournament::Tournament()
{
}

Tournament::Tournament(const int id, const std::vector<std::string>& strategies)
{
	mID = id;
	//Create a Prisoner for each strategy
	for (int i = 0; i < strategies.size(); i++)
	{
		mPrisoners.push_back(new Prisoner(strategies[i]));
	}
}

Tournament::~Tournament()
{
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		delete mPrisoners[i];
	}
	mPrisoners.clear();
}

void Tournament::play()
{
	std::cout << lineBreak;
	std::cout << "\nStrategy Name\t";
	for (int i = 0; i <= PsilLang::varEnums::ALLOUTCOMES_Z; i++)
	{
		std::cout << PsilLang::psilVars[i] << "\t";
	}
	std::cout << "\n";

	int gameNum = 1;
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		for (int j = i + 1; j < mPrisoners.size(); j++)
		{
			Game* game = new Game(mPrisoners[i], mPrisoners[j]);
			game->play(gameNum);
			gameNum++;
			delete game;
		}
	}
}

void Tournament::generateResults()
{
	std::ostringstream ossResults;
	ossResults << lineBreak;
	ossResults << "\nStrategy Name\t\tTotal Score\n\n";

	int winner = 0;
	//Print each prisoner's cumulative score and determine a winner (lowest score)
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		ossResults << mPrisoners[i]->getStrategyName() << "\t\t" << mPrisoners[i]->getVariable(PsilLang::varEnums::CUMULATIVE_SCORE) << "\n";

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
	printResults();
}

void Tournament::printResults()
{
	std::cout << mTournamentResults << "\n";
}
