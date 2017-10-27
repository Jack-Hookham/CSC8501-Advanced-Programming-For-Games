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

void Tournament::printTournamentHeading(const int gameDetail)
{
	switch (gameDetail)
	{
	case 0:
		break;
	case 1:
		std::cout << lineBreak;
		std::cout << std::setw(15) << "\nStrategy" << std::setw(PsiLang::psilVars[PsiLang::varEnums::MYSCORE].length() + 2) << PsiLang::psilVars[PsiLang::varEnums::MYSCORE];
		std::cout << "\n";
		std::cout << lineBreak;
		break;
	case 2:
		std::cout << lineBreak;
		std::cout << std::setw(15) << "\nStrategy";

		for (int i = 0; i <= PsiLang::varEnums::ALLOUTCOMES_Z; i++)
		{
			std::cout << std::setw(PsiLang::psilVars[i].length() + 2) << PsiLang::psilVars[i];
		}
		std::cout << "\n";
		std::cout << lineBreak;
		break;
	}
}

void Tournament::play(const int gameDetail)
{
	printTournamentHeading(gameDetail);

	for (int i = 0; i < mTournamentIterations; i++)
	{
		for (int j = 0; j < mPrisoners.size(); j++)
		{
			for (int k = j + 1; k < mPrisoners.size(); k++)
			{
				mGamesPlayed++;
				Game* game = new Game(mPrisoners[j], mPrisoners[k]);
				game->play(mGamesPlayed, mGameIterations, gameDetail);
				delete game;
			}
		}
	}
}

void Tournament::generateResults(const int tournamentDetail)
{
	std::ostringstream ossResults;
	int winner = 0;
	switch (tournamentDetail)
	{
	case 0:
		mTournamentResults = "";
		break;
	case 1:
		//Print each prisoner's cumulative score and determine a winner (lowest score)
		for (int i = 0; i < mPrisoners.size(); i++)
		{
			if (mPrisoners[i]->getVariable(PsiLang::varEnums::CUMULATIVE_SCORE) < mPrisoners[winner]->getVariable(PsiLang::varEnums::CUMULATIVE_SCORE))
			{
				winner = i;
			}
		}
		ossResults << lineBreak;
		ossResults << "\nTournament " << mID << " Results\n";
		ossResults << "\nWinning strategy: " << mPrisoners[winner]->getStrategyName() << "\n";
		ossResults << lineBreak;

		mTournamentResults = ossResults.str();
		break;
	case 2:
		ossResults << lineBreak;
		ossResults << "\nTournament " << mID << " Results\n";
		ossResults << "Number of Strategies: " << mNumStrategies << "   Tournament Iterations: " << mTournamentIterations << "   Game Iterations: " << mGameIterations << "\n";
		ossResults << lineBreak;
		ossResults << std::left << std::setw(15) << "\nStrategy ID" << "Total Score" << "\n\n";

		//Print each prisoner's cumulative score and determine a winner (lowest score)
		for (int i = 0; i < mPrisoners.size(); i++)
		{
			ossResults << std::left << std::setw(15) << mPrisoners[i]->getStrategyName() << mPrisoners[i]->getVariable(PsiLang::varEnums::CUMULATIVE_SCORE) << "\n";

			if (mPrisoners[i]->getVariable(PsiLang::varEnums::CUMULATIVE_SCORE) < mPrisoners[winner]->getVariable(PsiLang::varEnums::CUMULATIVE_SCORE))
			{
				winner = i;
			}
		}
		ossResults << lineBreak;
		ossResults << "\nWinning strategy: " << mPrisoners[winner]->getStrategyName() << "\n";
		ossResults << lineBreak;

		mTournamentResults = ossResults.str();
		break;
	}

	std::ostringstream path;
	path << resultsPath << "TournamentResults" << mID << ".txt";

	try
	{
		FileManager::writeToFile(path.str(), mTournamentResults);
	}
	catch (const std::invalid_argument& iae)
	{
		std::cout << "Invalid argument: " << iae.what() << "\n";
		exit(1);
	}

	std::cout << this;
}
