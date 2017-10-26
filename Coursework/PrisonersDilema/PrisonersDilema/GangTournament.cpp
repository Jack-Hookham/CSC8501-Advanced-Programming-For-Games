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
	mSpyChance = spyChance;

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

void GangTournament::play(const int gameDetail)
{
	printTournamentHeading(gameDetail);

	for (int i = 0; i < mTournamentIterations; i++)
	{
		for (int j = 0; j < mGangs.size(); j++)
		{
			for (int k = j + 1; k < mGangs.size(); k++)
			{
				mGamesPlayed++;
				GangGame* game = new GangGame(mGangs[j], mGangs[k], mSpyChance);
				game->play(mGamesPlayed, mGameIterations, gameDetail);
				delete game;
			}
		}
	}
}

void GangTournament::generateResults(const int tournamentDetail)
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
			if (mPrisoners[i]->getVariable(PsilLang::varEnums::CUMULATIVE_SCORE) < mPrisoners[winner]->getVariable(PsilLang::varEnums::CUMULATIVE_SCORE))
			{
				winner = i;
			}
		}
		ossResults << lineBreak;
		ossResults << "\nGang Tournament " << mID << " Results\n";
		ossResults << "\nWinning gang: " << mGangs[winner]->getName() << "\n\n";
		for (int i = 0; i < Gang::GANG_SIZE; i++)
		{
			ossResults << "Member " << i + 1 << " - " << mGangs[winner]->getMember(i)->getStrategyName() << "\n";
		}
		ossResults << lineBreak;

		mTournamentResults = ossResults.str();
		break;
	case 2:
		ossResults << lineBreak;
		ossResults << "\nGang Tournament " << mID << " Results\n";
		ossResults << "Number of Strategies: " << mNumStrategies << "   Tournament Iterations: " << mTournamentIterations << 
			"   Game Iterations: " << mGameIterations << "   Spy Chance: " << mSpyChance << "%" << "\n\n";
		ossResults << lineBreak;
		ossResults << "\n" << std::setw(70) << "Gang Member Strategies\n";
		ossResults << "\n" << std::left << std::setw(15) << "Gang Name" << std::setw(15) << "Total Score";
		for (int i = 0; i < Gang::GANG_SIZE; i++)
		{
			std::string s = "Member " + std::to_string(i + 1);
			ossResults << std::setw(15) << s;
		}
		ossResults << "\n\n";

		//Print each gang's cumulative score and determine a winner (lowest score)
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
		ossResults << "\nWinning gang: " << mGangs[winner]->getName() << "\n\n";
		for (int i = 0; i < Gang::GANG_SIZE; i++)
		{
			ossResults << "Member " << i + 1 << " - " << mGangs[winner]->getMember(i)->getStrategyName() << "\n";
		}
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

void GangTournament::printTournamentHeading(const int gameDetail)
{

	switch (gameDetail)
	{
	case 0:
		break;
	case 1:
		std::cout << lineBreak;
		std::cout << "\n" << std::left << std::setw(15) << "Gang" << std::setw(PsilLang::psilVars[PsilLang::varEnums::MYSCORE].length() + 2) << PsilLang::psilVars[PsilLang::varEnums::MYSCORE];
		std::cout << "\n";
		std::cout << lineBreak;
		break;
	case 2:
		std::cout << lineBreak;
		std::cout << "\n" << std::left << std::setw(15) << "Gang";

		for (int i = 0; i <= PsilLang::varEnums::ALLOUTCOMES_Z; i++)
		{
			std::cout << std::setw(PsilLang::psilVars[i].length() + 2) << PsilLang::psilVars[i];
		}	
		
		for (int i = PsilLang::varEnums::ALLOUTCOMES_A; i <= PsilLang::varEnums::ALLOUTCOMES_C; i++)
		{
			std::cout << std::setw(PsilLang::psilVars[i].length() + 2) << PsilLang::psilVars[i];
		}

		std::cout << "\n";
		std::cout << lineBreak;
		break;
	}
}
