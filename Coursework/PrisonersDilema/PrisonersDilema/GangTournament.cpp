#include "GangTournament.h"

GangTournament::GangTournament()
{
}

GangTournament::GangTournament(const int id, const std::vector<std::string>& strategies, const int gameIterations, const int tournamentIterations)
{
	mID = id;
	mNumStrategies = strategies.size();
	mGameIterations = gameIterations;
	mTournamentIterations = tournamentIterations;

	//Generate a prisoner for each strategy
	generatePrisoners(strategies);

	//Randomly populate each gang with new gang members from the selection of prisoners
	//Each gang members uses one of the strategies provided
	std::vector<GangMember*> purpleMembers;
	for (int i = 0; i < Gang::GANG_SIZE; i++)
	{
		int prisonerID = RandomGen::generateRandomWithinRange(0, mPrisoners.size() - 1);
		//mPrisoners[prisonerID]->setStrategy("../Strategies/Test/Betray.txt");
		purpleMembers.push_back(new GangMember(mPrisoners[prisonerID]));
	}
	mGangs.push_back(new Gang("Purple Hand", purpleMembers));

	std::vector<GangMember*> magentaMembers;
	for (int i = 0; i < Gang::GANG_SIZE; i++)
	{
		int prisonerID = RandomGen::generateRandomWithinRange(0, mPrisoners.size() - 1);
		//mPrisoners[prisonerID]->setStrategy("../Strategies/Test/Silence.txt");
		magentaMembers.push_back(new GangMember(mPrisoners[prisonerID]));
	}
	mGangs.push_back(new Gang("Magenta Hand", magentaMembers));

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
