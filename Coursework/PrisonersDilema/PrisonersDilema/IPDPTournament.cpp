#include "IPDPTournament.h"

IPDPTournament::IPDPTournament(const std::vector<std::string>& strategies)
{
	//Create a Prisoner for each strategy
	for (int i = 0; i < strategies.size(); i++)
	{
		mPrisoners.push_back(new Prisoner(strategies[i]));
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
	std::cout << lineBreak;
	std::cout << "\nStrategy Name\t";
	for (int i = 0; i <= PsilLang::varEnums::MYSCORE; i++)
	{
		std::cout << PsilLang::psilVars[i] << "\t";
	}
	std::cout << "\n";

	int gameNum = 1;
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		for (int j = i + 1; j < mPrisoners.size(); j++)
		{
			IPDPGame* game = new IPDPGame(mPrisoners[i], mPrisoners[j]);
			game->play(gameNum);
			gameNum++;
		}
	}
}

void IPDPTournament::printResults()
{
	std::cout << lineBreak;
	std::cout << "\nStrategy Name\t\tTotal Score\n\n";

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
	std::cout << lineBreak;
	std::cout << "\nWinning strategy: " << mPrisoners[winner]->getStrategyName() << "\n";
	std::cout << lineBreak;
}
