#include "GangTournament.h"

GangTournament::GangTournament()
{
}

GangTournament::GangTournament(const int id, const std::vector<std::string>& strategies, const int gameIterations, const int tournamentIterations, 
	const int numGangs, const int spyChance)
{
	const int gangSize = 5;
	mID = id;
	mNumStrategies = strategies.size();
	mGameIterations = gameIterations;
	mTournamentIterations = tournamentIterations;
	mSpychance = spyChance;

	//Generate a prisoner for each strategy
	generatePrisoners(strategies);
	//Track the number of strategies used to ensure that all strategies get used
	int strategiesUsed = 0;
	//Randomly populate each gang with new gang members from the selection of prisoners
	//Each gang members uses one of the strategies provided
	for (int i = 0; i < numGangs; i++)
	{
		std::vector<GangMember*> gangMembers;
		for (int j = 0; j < gangSize; j++)
		{
			int prisonerID;
			//ensure each strategy is used at least once
			if (strategiesUsed < strategies.size())
			{
				prisonerID = strategiesUsed;
				strategiesUsed++;
			}
			else
			{
				prisonerID = RandomGen::generateRandomWithinRange(0, mPrisoners.size() - 1);
			}

			gangMembers.push_back(new GangMember(mPrisoners[prisonerID]));
		}
		mGangs.push_back(new Gang(i + 1, gangMembers));
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
				GangGame* game = new GangGame(mGangs[j], mGangs[k], mSpychance);
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
	ossResults << std::setw(70) << "Gang Member Strategies\n";
	ossResults << std::left << std::setw(15) << "Gang Name" << std::setw(15) << "Total Score";
	for (int i = 0; i < Gang::GANG_SIZE; i++)
	{
		std::string s = "Member " + std::to_string(i + 1);
		ossResults << std::setw(15) << s;
	}
	ossResults << "\n\n";

	int winner = 0;
	//Print each prisoner's cumulative score and determine a winner (lowest score)
	for (int i = 0; i < mGangs.size(); i++)
	{
		ossResults << std::left << std::setw(15) << mGangs[i]->getName() << std::setw(15) << mGangs[i]->getCumulativeScore();
		for (int j = 0; j < Gang::GANG_SIZE; j++)
		{
			ossResults << std::setw(15) << mGangs[i]->getMember(j)->getStrategyName();
		}
		ossResults << "\n";

		if (mGangs[i]->getCumulativeScore() < mGangs[winner]->getCumulativeScore())
		{
			winner = i;
		}
	}
	ossResults << lineBreak;
	ossResults << "\nWinning gang: " << mGangs[winner]->getName() << "\n";
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
