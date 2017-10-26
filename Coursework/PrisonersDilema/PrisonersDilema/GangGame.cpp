#include "GangGame.h"
#include "Random.h"

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
	//Play n games
	for (int i = 0; i < gameIterations; i++)
	{
		addSpy(mGangA);
		addSpy(mGangB);

		int decisionsA[Gang::GANG_SIZE];
		int decisionsB[Gang::GANG_SIZE];

		//Get a decision for every prisoner in both gangs
		for (int j = 0; j < Gang::GANG_SIZE; j++)
		{
			decisionsA[j] = Interpreter::interpretDecision(mGangA->getMember(j));
			decisionsB[j] = Interpreter::interpretDecision(mGangB->getMember(j));

			if (decisionsA[j] == Prisoner::decisions::INVALID_FILE || decisionsB[j] == Prisoner::decisions::INVALID_FILE)
			{
				std::cout << "Invalid file! Game aborted.\n";

				mGangA->softReset();
				mGangB->softReset();

				return;
			}
		}
		updateVariables(decisionsA, decisionsB);

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
			<< std::setw(PsilLang::psilVars[PsilLang::varEnums::MYSCORE].length() + 2) << mGangA->getScore() << "\n";
		std::cout << std::setw(15) << std::left << mGangB->getName()
			<< std::setw(PsilLang::psilVars[PsilLang::varEnums::MYSCORE].length() + 2) << mGangB->getScore() << "\n";
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

void GangGame::addSpy(Gang* g)
{
	std::vector<double> spyWeights = { (100.0 - mSpyChance), (double)mSpyChance };

	//Determine whether this gang contains a spy
	bool spyInGang;
	if (RandomGen::generateRandomWeighted(spyWeights) == 0)
	{
		spyInGang = false;
	}
	else
	{
		spyInGang = true;
	}

	//If a spy is needed then generate its index
	if (spyInGang)
	{
		int spyIndex = RandomGen::generateRandomWithinRange(0, Gang::GANG_SIZE - 1);
		g->setSpy(spyIndex);
	}
}

void GangGame::updateVariables(const int decisionsA[], const int decisionsB[])
{
	mGangA->incrementIterations();
	mGangB->incrementIterations();

	//+1 for silence, -1 for betray
	int silenceCountA = 0;
	int silenceCountB = 0;

	//Adjust decision counters based on gang member decisions
	for (int i = 0; i < Gang::GANG_SIZE; i++)
	{
		if (decisionsA[i] == Prisoner::decisions::SILENCE) { silenceCountA++; }
		else { silenceCountA--; }

		if (decisionsB[i] == Prisoner::decisions::SILENCE){ silenceCountB++; }
		else{ silenceCountB--; }
	}

	//Silence count will = GANG_SIZE if all members were silent
	//Silence count will = -GANG_SIZE if all members betrayed

	//All members of both gangs were silent
	if (silenceCountA == Gang::GANG_SIZE && silenceCountB == Gang::GANG_SIZE)
	{
		mGangA->outcomeW();
		mGangB->outcomeW();
	}
	//Gang A all silent, gang B all betray
	else if (silenceCountA == Gang::GANG_SIZE && silenceCountB == -Gang::GANG_SIZE)
	{
		mGangA->outcomeX();
		mGangB->outcomeY();
	}
	//Gang A all betray, gang B all silent
	else if (silenceCountA == -Gang::GANG_SIZE && silenceCountB == Gang::GANG_SIZE)
	{
		mGangA->outcomeY();
		mGangB->outcomeX();
	}
	//All members of both gangs betray
	else if (silenceCountA == -Gang::GANG_SIZE && silenceCountB == -Gang::GANG_SIZE)
	{
		mGangA->outcomeZ();
		mGangB->outcomeZ();
	}
	//Mixed and equal
	else if (silenceCountA == silenceCountB)
	{
		mGangA->outcomeC();
		mGangB->outcomeC();
	}
	//Mixed, A most betrays
	else if (silenceCountA < silenceCountB)
	{
		mGangA->outcomeA();
		mGangB->outcomeB();
	}
	//Mixed, A least betrays
	else if (silenceCountA > silenceCountB)
	{
		mGangA->outcomeB();
		mGangB->outcomeA();
	}
	else
	{
		std::cout << "Unable to determine an outcome.\n";
	}
}
