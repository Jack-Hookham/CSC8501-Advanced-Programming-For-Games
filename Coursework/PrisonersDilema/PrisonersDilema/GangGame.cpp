#include "GangGame.h"
#include "Util.h"

GangGame::GangGame()
{
}

GangGame::GangGame(Gang* a, Gang* b, int spyChance)
{
	mGangA = a;
	mGangB = b;
	mSpyChance = spyChance;
}

GangGame::~GangGame()
{
}

void GangGame::play(const int gamesPlayed, const int gameIterations, const int gameDetail)
{
	bool leaderChange = true;
	//Play n games
	for (int i = 0; i < gameIterations; i++)
	{
		//Store the index of the spy in each gang (no spy = -1)
		int spyIndexA = addSpy(mGangA);
		int spyIndexB = addSpy(mGangB);

		int decisionsA[Gang::GANG_SIZE] = { -1, -1, -1, -1, -1 };
		int decisionsB[Gang::GANG_SIZE] = { -1, -1, -1, -1, -1 };

		//Get a decision for every prisoner in both gangs except the spy
		for (int j = 0; j < Gang::GANG_SIZE; j++)
		{
			if (j != spyIndexA)
			{
				decisionsA[j] = Interpreter::interpretDecision(mGangA->getMember(j));
			}

			if (j != spyIndexB)
			{
				decisionsB[j] = Interpreter::interpretDecision(mGangB->getMember(j));
			}

			if (decisionsA[j] == Prisoner::decisions::INVALID_FILE || decisionsB[j] == Prisoner::decisions::INVALID_FILE)
			{
				std::cout << "Invalid file! Game aborted.\n";

				mGangA->softReset();
				mGangB->softReset();

				return;
			}
		}

		//+1 for silence, -1 for betray
		int silenceCountA = 0;
		int silenceCountB = 0;

		//Adjust decision counters based on gang member decisions
		for (int i = 0; i < Gang::GANG_SIZE; i++)
		{
			if (decisionsA[i] == Prisoner::decisions::SILENCE) { silenceCountA++; }
			else if (decisionsA[i] == Prisoner::decisions::BETRAY) { silenceCountA--; }

			if (decisionsB[i] == Prisoner::decisions::SILENCE) { silenceCountB++; }
			else if (decisionsB[i] == Prisoner::decisions::BETRAY) { silenceCountB--; }
		}

		bool spyFoundA = false;
		bool spyFoundB = false;

		//After getting decisions for all none spies, determine the spy decisions
		if (spyIndexA > 0)
		{
			//if equal number of betrays and silences use spy's strategy
			if (silenceCountA == 0)
			{
				decisionsA[spyIndexA] = Interpreter::interpretDecision(mGangA->getMember(spyIndexA));
			}
			//if more silences than betrays spy betrays
			else if (silenceCountA > 0)
			{
				decisionsA[spyIndexA] = Prisoner::decisions::BETRAY;
			}
			//if more betrays than silences spy betrays
			else
			{
				decisionsA[spyIndexA] = Prisoner::decisions::SILENCE;
			}

			//Add decison to counter
			if (decisionsA[spyIndexA] == Prisoner::decisions::SILENCE) { silenceCountA++; }
			else { silenceCountA--; }

			//Determine whether the spy is found
			spyFoundA = findSpy(mGangA, spyIndexA, leaderChange);
		}

		if (spyIndexB > 0)
		{
			//if equal number of betrays and silences use spy's strategy
			if (silenceCountB == 0)
			{
				decisionsB[spyIndexB] = Interpreter::interpretDecision(mGangA->getMember(spyIndexB));
			}
			//if more silences than betrays spy betrays
			else if (silenceCountB > 0)
			{
				decisionsB[spyIndexB] = Prisoner::decisions::BETRAY;
			}
			//if more betrays than silences spy betrays
			else
			{
				decisionsB[spyIndexB] = Prisoner::decisions::SILENCE;
			}

			//Add decison to counter
			if (decisionsB[spyIndexB] == Prisoner::decisions::SILENCE) { silenceCountB++; }
			else { silenceCountB--; }

			//Determine whether the spy is found
			spyFoundB = findSpy(mGangB, spyIndexB, leaderChange);
		}

		bool scoreUpdated;

		//if a spy is found update variables based on leader decision rather than continuing with the usual variable updates
		if (spyFoundA && !spyFoundB)
		{
			//Leader stays and spy is discovered - 0 years
			//Leader changes and spy is discovered - 2 years
			if (leaderChange)
			{
				mGangA->addToScore(2.0f);
			}
			//Other gang in both cases - 5 years
			mGangB->addToScore(5.0f);
			scoreUpdated = true;
		}
		else if (!spyFoundA && spyFoundB)
		{
			if (leaderChange)
			{
				mGangB->addToScore(2.0f);
			}
			mGangA->addToScore(5.0f);
			scoreUpdated = true;
		}
		else if (spyFoundA && spyFoundB)
		{
			mGangA->addToScore(6.0f);
			mGangB->addToScore(6.0f); 
			scoreUpdated = true;
		}
		else
		{
			scoreUpdated = false;
		}

		updateVariables(silenceCountA, silenceCountB, scoreUpdated);

		mGangA->removeSpies();
		mGangB->removeSpies();
	}
	//Print the variables for both gangs at the end of the game
	switch (gameDetail)
	{
	case 0:
		break;
	case 1:
		std::cout << "\nGame " << gamesPlayed << "\n";
		std::cout << std::setw(15) << std::left << mGangA->getName()
			<< std::setw(PsiLang::psilVars[PsiLang::varEnums::MYSCORE].length() + 2) << mGangA->getScore() << "\n";
		std::cout << std::setw(15) << std::left << mGangB->getName()
			<< std::setw(PsiLang::psilVars[PsiLang::varEnums::MYSCORE].length() + 2) << mGangB->getScore() << "\n";
		break;
	case 2:
		std::cout << "\nGame " << gamesPlayed << "\n";
		std::cout << mGangA;
		std::cout << mGangB;
		break;
	}

	//Add scores to cumulative scores
	mGangA->addScore();
	mGangB->addScore();

	//Reset the variables after the game
	mGangA->softReset();
	mGangB->softReset();
}

const int GangGame::addSpy(Gang* g)
{
	std::vector<double> spyWeights = { (100.0 - mSpyChance), (double)mSpyChance };
	int spyIndex;
	//Determine whether this gang contains a spy
	if (RandomGen::generateRandomWeighted(spyWeights) == 1)
	{
		g->incrementTotalSpies();
		spyIndex = RandomGen::generateRandomWithinRange(0, Gang::GANG_SIZE - 1);
		g->setSpy(spyIndex);
	}
	else
	{
		spyIndex = -1;
	}
	return spyIndex;
}

const bool GangGame::findSpy(Gang* g, const int spyIndex, const bool leaderChange)
{
	//Member index of the leader's spy choice - cannot choose himself
	int leaderChoice = RandomGen::generateRandomWithinRange(1, Gang::GANG_SIZE - 1);

	//Change choice if required
	if (leaderChange)
	{
		//Weightings for each index to be revealed
		//Leader weighting set to 0
		std::vector<double>revealDistribution = { 0, 1, 1, 1, 1 };
		//Spy weighting set to 0
		revealDistribution[spyIndex] = 0;
		//Leader choice weighting set to 0
		revealDistribution[leaderChoice] = 0;
		//Index of a member who is not the leader, not the spy and not the leader's choice
		int revealIndex = RandomGen::generateRandomWeighted(revealDistribution);

		//Weightings for leader's second choice
		std::vector<double>secondChoiceDistribution = { 0, 1, 1, 1, 1 };
		secondChoiceDistribution[leaderChoice] = 0;
		secondChoiceDistribution[revealIndex] = 0;
		leaderChoice = RandomGen::generateRandomWeighted(secondChoiceDistribution);
	}

	//If the leader choice and spy indexes are the same then the spy was found
	if (leaderChoice == spyIndex)
	{
		g->incrementDiscoveredSpies();
		return true;
	}
	else
	{
		return false;
	}
}

void GangGame::updateVariables(const int silenceCountA, const int silenceCountB, const bool scoreUpdated)
{
	mGangA->incrementIterations();
	mGangB->incrementIterations();

	//Silence count will = GANG_SIZE if all members were silent
	//Silence count will = -GANG_SIZE if all members betrayed

	//Outcomes pass updated bools so that the scores are only updated if they haven't already been updated due to the leader discovering the spy
	//All members of both gangs were silent
	if (silenceCountA == Gang::GANG_SIZE && silenceCountB == Gang::GANG_SIZE)
	{
		mGangA->outcomeW(scoreUpdated);
		mGangB->outcomeW(scoreUpdated);
	}
	//Gang A all silent, gang B all betray
	else if (silenceCountA == Gang::GANG_SIZE && silenceCountB == -Gang::GANG_SIZE)
	{
		mGangA->outcomeX(scoreUpdated);
		mGangB->outcomeY(scoreUpdated);
	}
	//Gang A all betray, gang B all silent
	else if (silenceCountA == -Gang::GANG_SIZE && silenceCountB == Gang::GANG_SIZE)
	{
		mGangA->outcomeY(scoreUpdated);
		mGangB->outcomeX(scoreUpdated);
	}
	//All members of both gangs betray
	else if (silenceCountA == -Gang::GANG_SIZE && silenceCountB == -Gang::GANG_SIZE)
	{
		mGangA->outcomeZ(scoreUpdated);
		mGangB->outcomeZ(scoreUpdated);
	}
	//Mixed and equal
	else if (silenceCountA == silenceCountB)
	{
		mGangA->outcomeC(scoreUpdated);
		mGangB->outcomeC(scoreUpdated);
	}
	//Mixed, A most betrays
	else if (silenceCountA < silenceCountB)
	{
		mGangA->outcomeA(scoreUpdated);
		mGangB->outcomeB(scoreUpdated);
	}
	//Mixed, A least betrays
	else if (silenceCountA > silenceCountB)
	{
		mGangA->outcomeB(scoreUpdated);
		mGangB->outcomeA(scoreUpdated);
	}
}
