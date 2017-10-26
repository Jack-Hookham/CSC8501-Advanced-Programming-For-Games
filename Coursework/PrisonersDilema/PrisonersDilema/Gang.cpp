#include "Gang.h"

Gang::Gang()
{
}

Gang::Gang(const int id, const std::vector<GangMember*>& gangMembers)
{
	mName = "Gang " + std::to_string(id);
	mGangMembers = gangMembers;

	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::UNKOWN_DECISION;
}

Gang::~Gang()
{
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		delete mGangMembers[i];
	}
	mGangMembers.clear();
}

void Gang::addToScore(const float x)
{
	mScore += x;
	for (int i = 0; i < GANG_SIZE; i++)
	{
		mGangMembers[i]->addToScore(x);
	}
}

void Gang::softReset()
{
	for (int i = 0; i < PsiLang::varEnums::UNKOWN_DECISION; i++)
	{
		mVariables[i] = 0;
	}
	mScore = 0.0f;
	mTotalSpies = 0;
	mDiscoveredSpies = 0;

	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->softReset();
	}
}

void Gang::hardReset()
{
	for (int i = 0; i < PsiLang::varEnums::CUMULATIVE_SCORE; i++)
	{
		mVariables[i] = 0;
	}
	mScore = 0.0f;
	mCScore = 0.0f;
	mTotalSpies = 0;
	mDiscoveredSpies = 0;

	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->hardReset();
	}
}

void Gang::addScore()
{
	mCScore += mScore;
	mCTotalSpies += mTotalSpies;
	mCDiscoveredSpies += mDiscoveredSpies;
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->addScore();
	}
}

void Gang::incrementIterations()
{
	mVariables[PsiLang::varEnums::ITERATIONS]++;
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->incrementIterations();
	}
}

std::ostream& operator<<(std::ostream& os, const Gang* g)
{
	std::ostringstream ossID;
	ossID << g->getName();
	os << std::setw(15) << std::left << ossID.str();
	for (int i = PsiLang::varEnums::LASTOUTCOME; i <= PsiLang::varEnums::ALLOUTCOMES_Z; i++)
	{
		//If LASTOUTCOME print the letter, otherwise print int value of the variable
		if (i == PsiLang::varEnums::LASTOUTCOME)
		{
			os << std::setw(PsiLang::psilVars[i].length() + 2) << PsiLang::psilVars[g->getVariable(i)];
		}
		//If MYSCORE print var as it's stored as a double and not in the array
		else if (i == PsiLang::varEnums::MYSCORE)
		{
			os << std::setw(PsiLang::psilVars[i].length() + 2) << g->getScore();
		}
		//If CUMULATIVE_SCORE print var as it's stored as a double and not in the array
		else if (i == PsiLang::varEnums::CUMULATIVE_SCORE)
		{
			os << std::setw(PsiLang::psilVars[i].length() + 2) << g->getCumulativeScore();
		}
		else
		{
			os << std::setw(PsiLang::psilVars[i].length() + 2) << g->getVariable(i);
		}
	}	
	
	for (int i = PsiLang::varEnums::ALLOUTCOMES_A; i <= PsiLang::varEnums::ALLOUTCOMES_C; i++)
	{
		os << std::setw(PsiLang::psilVars[i].length() + 2) << g->getVariable(i);
	}

	//Spy vars
	std::string s = "Spy Count";
	os << std::setw(s.length() + 2) << g->getTotalSpies();
	s = "Spies Discovered";
	os << std::setw(s.length() + 2) << g->getDiscoveredSpies();
	os << "\n";
	return os;
}

//Both silent
void Gang::outcomeW(const bool updated)
{
	//Update the score if it hasn't already been updated due to the leader finding the spy
	if (!updated)
	{
		mScore += 2;
	}
	mVariables[PsiLang::varEnums::ALLOUTCOMES_W]++;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::W;
	
	//Update the relevant prisoner vars
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->outcomeW(updated);
	}
}

//A silent, B betray
void Gang::outcomeX(const bool updated)
{	//Update the score if it hasn't already been updated due to the leader finding the spy
	if (!updated)
	{
		mScore += 5;
	}
	mVariables[PsiLang::varEnums::ALLOUTCOMES_X]++;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::X;

	//Update the relevant prisoner vars
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->outcomeX(updated);
	}
}

//A betray, B silent
void Gang::outcomeY(const bool updated)
{
	mVariables[PsiLang::varEnums::ALLOUTCOMES_Y]++;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::Y;

	//Update the relevant prisoner vars
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->outcomeY(updated);
	}
}

//Both betray
void Gang::outcomeZ(const bool updated)
{	//Update the score if it hasn't already been updated due to the leader finding the spy
	if (!updated)
	{
		mScore += 4;
	}
	mVariables[PsiLang::varEnums::ALLOUTCOMES_Z]++;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::Z;

	//Update the relevant prisoner vars
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->outcomeZ(updated);
	}
}

//Mixed, most betrays
void Gang::outcomeA(const bool updated)
{	//Update the score if it hasn't already been updated due to the leader finding the spy
	if (!updated)
	{
		mScore += 2.5;
	}
	mVariables[PsiLang::varEnums::ALLOUTCOMES_A]++;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::A;

	//Update the relevant prisoner vars
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->outcomeA(updated);
	}
}

//Mixed, least betrays
void Gang::outcomeB(const bool updated)
{	//Update the score if it hasn't already been updated due to the leader finding the spy
	if (!updated)
	{
		mScore += 3;
	}
	mVariables[PsiLang::varEnums::ALLOUTCOMES_B]++;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::B;

	//Update the relevant prisoner vars
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->outcomeB(updated);
	}
}

//Mixed, equal
void Gang::outcomeC(const bool updated)
{	
	//Update the score if it hasn't already been updated due to the leader finding the spy
	if (!updated)
	{
		mScore += 2;
	}
	mVariables[PsiLang::varEnums::ALLOUTCOMES_C]++;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::C;

	//Update the relevant prisoner vars
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->outcomeC(updated);
	}
}

void Gang::setSpy(const int index)
{
	mGangMembers[index]->setSpy(true);
}

void Gang::removeSpies()
{
	for (int i = 0; i < GANG_SIZE; i++)
	{
		mGangMembers[i]->setSpy(false);
	}
}
