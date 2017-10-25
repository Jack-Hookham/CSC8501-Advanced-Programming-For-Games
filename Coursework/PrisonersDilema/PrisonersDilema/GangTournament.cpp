#include "GangTournament.h"

GangTournament::GangTournament()
{
}

GangTournament::GangTournament(const int id, const std::vector<std::string>& strategies, const int gameIterations, const int tournamentIterations, const int numGangs)
{
	const int gangSize = 5;
	mID = id;
	mNumStrategies = strategies.size();
	mGameIterations = gameIterations;
	mTournamentIterations = tournamentIterations;

	//Generate a prisoner for each strategy
	generatePrisoners(strategies);
	//Randomly populate each gang with new gang members from the selection of prisoners
	//Each gang members uses one of the strategies provided
	for (int i = 0; i < numGangs; i++)
	{
		std::vector<GangMember*> gangMembers;
		for (int i = 0; i < gangSize; i++)
		{
			int prisonerID = RandomGen::generateRandomWithinRange(0, mPrisoners.size() - 1);
			gangMembers.push_back(new GangMember(mPrisoners[prisonerID]));
		}
		mGangs.push_back(new Gang(i + 1, gangMembers));
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
	printGangs();

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
	std::ostringstream ossResults;
	ossResults << lineBreak;
	ossResults << "\nNumber of Strategies: " << mNumStrategies << "   Tournament Iterations: " << mTournamentIterations << "   Game Iterations: " << mGameIterations << "\n\n";
	ossResults << std::left << std::setw(15) << "Strategy Name" << "Total Score" << "\n\n";

	int winner = 0;
	//Print each prisoner's cumulative score and determine a winner (lowest score)
	for (int i = 0; i < mGangs.size(); i++)
	{
		ossResults << std::left << std::setw(15) << mGangs[i]->getName() << mGangs[i]->getCumulativeScore() << "\n";

		if (mGangs[i]->getCumulativeScore() < mGangs[winner]->getCumulativeScore())
		{
			winner = i;
		}
	}
	ossResults << lineBreak;
	ossResults << "\nWinning strategy: " << mGangs[winner]->getName() << "\n";
	ossResults << lineBreak;

	mTournamentResults = ossResults.str();
	std::ostringstream path;
	path << resultsPath << "TournamentResults" << mID << ".txt";
	FileManager::writeToFile(path.str(), mTournamentResults);
	std::cout << this;
}

void GangTournament::printGangs()
{
	for (int i = 0; i < mGangs.size(); i++)
	{
		std::cout << mGangs[i]->getName() << "\n";
		for (int j = 0; j < mGangs[i]->getMembers().size(); j++)
		{
			std::cout << mGangs[i]->getMember(j)->getStrategyName() << "\n";
		}
		std::cout << "\n";
	}
}

void GangTournament::printTournamentHeading()
{
	std::cout << lineBreak;
	std::cout << std::setw(15) << "\nGang Name";

	for (int i = PsilLang::varEnums::LASTOUTCOME; i <= PsilLang::varEnums::ALLOUTCOMES_Z; i++)
	{
		std::cout << std::setw(PsilLang::psilVars[i].length() + 2) << PsilLang::psilVars[i];
	}

	for (int i = PsilLang::varEnums::ALLOUTCOMES_A; i <= PsilLang::varEnums::ALLOUTCOMES_C; i++)
	{
		std::cout << std::setw(PsilLang::psilVars[i].length() + 2) << PsilLang::psilVars[i];
	}
	std::cout << "\n";
	std::cout << lineBreak;
}
