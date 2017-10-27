#include "GangTournament.h"

GangTournament::GangTournament()
{
}

GangTournament::GangTournament(const int id, const std::vector<std::string>& strategies, const bool leaderChoice, const int gameIterations, 
	const int tournamentIterations, const int numGangs, const int spyChance)
{
	mID = id;
	mNumStrategies = strategies.size();
	mGameIterations = gameIterations;
	mTournamentIterations = tournamentIterations;
	mSpyChance = spyChance;
	mLeaderChange = leaderChoice;

	//Generate a prisoner for each strategy
	generatePrisoners(strategies);

	//Randomly populate each gang with new gang members from the selection of prisoners
	//Each gang members uses one of the strategies provided
	for (int i = 0; i < numGangs; i++)
	{
		std::vector<GangMember*> gangMembers;
		for (int j = 0; j < Gang::GANG_SIZE; j++)
		{
			int prisonerID = RandomGen::generateRandomWithinRange(0, mPrisoners.size() - 1);
			gangMembers.push_back(new GangMember(mPrisoners[prisonerID]));
		}
		mGangs.push_back(new Gang(i + 1, gangMembers));
	}

	//Track the number of strategies used to ensure that all strategies get used
	int strategiesUsed = 0;
	std::vector<double> gangDist(numGangs * Gang::GANG_SIZE, 1);
	while (strategiesUsed < strategies.size() && strategiesUsed < numGangs * Gang::GANG_SIZE )
	{
		int gangIndex = RandomGen::generateRandomWeighted(gangDist);
		gangDist[gangIndex] = 0;
		int gangID = gangIndex / Gang::GANG_SIZE;
		gangIndex = gangIndex % Gang::GANG_SIZE;
		mGangs[gangID]->setMember(gangIndex, new GangMember(mPrisoners[strategiesUsed]));
		strategiesUsed++;
	}

	//Set the first member of each gang as the leader
	for (int i = 0; i < numGangs; i++)
	{
		mGangs[i]->setLeader(0);
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
	//Reset variables
	for (int i = 0; i < mGangs.size(); i++)
	{
		mGangs[i]->hardReset();
	}
	printTournamentHeading(gameDetail);

	for (int i = 0; i < mTournamentIterations; i++)
	{
		for (int j = 0; j < mGangs.size(); j++)
		{
			for (int k = j + 1; k < mGangs.size(); k++)
			{
				mGamesPlayed++;
				GangGame* game = new GangGame(mGangs[j], mGangs[k], mSpyChance);
				game->play(mGamesPlayed, mLeaderChange, mGameIterations, gameDetail);
				delete game;
			}
		}
	}
}

void GangTournament::generateResults(const int tournamentDetail)
{
	//Calculate the percentage of discovered spies
	float discoveredPercent = 100.0f;
	int totalSpies = 0;
	int totalDiscovered = 0;
	if (mSpyChance > 0)
	{
		for (int i = 0; i < mGangs.size(); i++)
		{
			totalSpies += mGangs[i]->getCTotalSpies();
			totalDiscovered += mGangs[i]->getCDiscoveredSpies();
		}
		try
		{
			discoveredPercent = util::computePercent((float)totalDiscovered, (float)totalSpies);
		}
		catch (const std::invalid_argument& iae)
		{
			std::cout << "Unable to compute average: " << iae.what() << "\n";
		}
	}

	std::ostringstream ossResults;
	int winner = 0;
	switch (tournamentDetail)
	{
	case 0:
		mTournamentResults = "";
		break;
	case 1:
		//Print each gang's cumulative score and determine a winner (lowest score)
		for (int i = 0; i < mPrisoners.size(); i++)
		{
			if (mPrisoners[i]->getVariable(PsiLang::varEnums::CUMULATIVE_SCORE) < mPrisoners[winner]->getVariable(PsiLang::varEnums::CUMULATIVE_SCORE))
			{
				winner = i;
			}
		}
		ossResults << lineBreak;
		ossResults << "\nGang Tournament " << mID << " Results\n";
		ossResults << "\nWinning Combination: " << mGangs[winner]->getName() << "\n\n";
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
			"   Game Iterations: " << mGameIterations << "   Spy Chance: " << mSpyChance << "%" << "\n";
		ossResults << lineBreak;
		ossResults << "\n" << std::setw(70) << "Gang Member Strategies\n";
		ossResults << "\n" << std::left << std::setw(15) << "Gang Name" << std::setw(15) << "Total Score";
		for (int i = 0; i < Gang::GANG_SIZE; i++)
		{
			std::string s = "Member " + std::to_string(i + 1);
			ossResults << std::setw(15) << s;
		}
		ossResults << "\n\n";

		float avgScore = 0.0f;
		//Print each gang's cumulative score and determine a winner (lowest score)
		for (int i = 0; i < mGangs.size(); i++)
		{
			avgScore += mGangs[i]->getCumulativeScore();
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
		avgScore /= mGangs.size();

		ossResults << "\n";
		std::string choice;
		if (mSpyChance < 0) { choice = "N/A"; }
		else if (mLeaderChange) { choice = "Yes"; } 
		else { choice = "No"; }

		ossResults << "Average Score: " << std::fixed << std::setprecision(1) << avgScore << "\n";
		ossResults << "Leader Changes Choice: " << choice << "\n";
		ossResults << "Total Spies: " << totalSpies << "\n";
		ossResults << "Total Spies Discovered: " << totalDiscovered << "\n";
		ossResults << "Percent Discovered: " << std::setprecision(1) << discoveredPercent << "%\n";
		ossResults << lineBreak;
		ossResults << "\nWinning Combination: " << mGangs[winner]->getName() << "\n\n";
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
		std::cout << "\n" << std::left << std::setw(15) << "Gang" << std::setw(PsiLang::psilVars[PsiLang::varEnums::MYSCORE].length() + 2) << PsiLang::psilVars[PsiLang::varEnums::MYSCORE];
		std::cout << "\n";
		std::cout << lineBreak;
		break;
	case 2:
		std::cout << lineBreak;
		std::cout << "\n" << std::left << std::setw(15) << "Gang";

		for (int i = 0; i <= PsiLang::varEnums::ALLOUTCOMES_Z; i++)
		{
			std::cout << std::setw(PsiLang::psilVars[i].length() + 2) << PsiLang::psilVars[i];
		}
		
		for (int i = PsiLang::varEnums::ALLOUTCOMES_A; i <= PsiLang::varEnums::ALLOUTCOMES_C; i++)
		{
			std::cout << std::setw(PsiLang::psilVars[i].length() + 2) << PsiLang::psilVars[i];
		}

		//Spy headings
		std::string s = "Spy Count";
		std::cout << std::setw(s.length() + 2) << s;
		s = "Spies Discovered";
		std::cout << std::setw(s.length() + 2) << s;

		std::cout << "\n";
		std::cout << lineBreak;
		break;
	}
}
