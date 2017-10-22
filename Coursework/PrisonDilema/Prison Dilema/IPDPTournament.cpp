#include "IPDPTournament.h"

IPDPTournament::IPDPTournament(std::vector<std::string> strategies)
{
	//Create a Prisoner for each strategy
	for (int i = 0; i < strategies.size(); i++)
	{
		Prisoner* prisoner = new Prisoner(strategies[i]);
		mPrisoners.push_back(prisoner);
	}
}

IPDPTournament::~IPDPTournament()
{
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		delete mPrisoners[i];
	}
	mPrisoners.clear();
}

void IPDPTournament::play()
{
	std::cout << "Strategy Name\t";
	for (int i = 0; i <= PsilLang::varEnums::MYSCORE; i++)
	{
		std::cout << PsilLang::psilVars[i] << "\t";
	}
	std::cout << "\n";

	for (int i = 0; i < mPrisoners.size(); i++)
	{
		for (int j = i + 1; j < mPrisoners.size(); j++)
		{
			IPDPGame* game = new IPDPGame(mPrisoners[i], mPrisoners[j]);
			game->play();
		}
	}
}

void IPDPTournament::printResults()
{
	std::cout << "Strategy Name\tTotal Score\n";

	int winner = 0;
	//Print each prisoner's cumulative score and determine a winner (lowest score)
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		std::cout << mPrisoners[i]->getStrategyName() << "\t\t" << mPrisoners[i]->getVariable(PsilLang::varEnums::CUMULATIVE_SCORE) << "\n";

		if (mPrisoners[i]->getVariable(PsilLang::varEnums::CUMULATIVE_SCORE) < mPrisoners[winner]->getVariable(PsilLang::varEnums::CUMULATIVE_SCORE))
		{
			winner = i;
		}
	}
	std::cout << "Winning strategy: " << mPrisoners[winner]->getStrategyName() << "\n";
}
