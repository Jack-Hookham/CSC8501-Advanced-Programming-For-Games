#include "Gang.h"

Gang::Gang()
{
}

Gang::Gang(const int id, const std::vector<GangMember*>& gangMembers)
{
	mName = "Gang " + std::to_string(id);
	mGangMembers = gangMembers;

	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::UNKOWN_DECISION;
}

Gang::~Gang()
{
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		delete mGangMembers[i];
	}
	mGangMembers.clear();
}

void Gang::softReset()
{
	for (int i = 0; i < PsilLang::varEnums::UNKOWN_DECISION; i++)
	{
		mVariables[i] = 0;
	}
	mScore = 0.0f;

	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->softReset();
	}
}

void Gang::hardReset()
{
	for (int i = 0; i < PsilLang::varEnums::CUMULATIVE_SCORE; i++)
	{
		mVariables[i] = 0;
	}
	mCumulativeScore = 0.0f;

	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->hardReset();
	}
}

void Gang::addScore()
{
	mCumulativeScore += mScore;
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->addScore();
	}
}

void Gang::incrementIterations()
{
	mVariables[PsilLang::varEnums::ITERATIONS]++;
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
	for (int i = PsilLang::varEnums::LASTOUTCOME; i <= PsilLang::varEnums::ALLOUTCOMES_Z; i++)
	{
		//If LASTOUTCOME print the letter, otherwise print int value of the variable
		if (i == PsilLang::varEnums::LASTOUTCOME)
		{
			os << std::setw(PsilLang::psilVars[i].length() + 2) << PsilLang::psilVars[g->getVariable(i)];
		}
		//If MYSCORE print var as it's stored as a double and not in the array
		else if (i == PsilLang::varEnums::MYSCORE)
		{
			os << std::setw(PsilLang::psilVars[i].length() + 2) << g->getScore();
		}
		//If CUMULATIVE_SCORE print var as it's stored as a double and not in the array
		else if (i == PsilLang::varEnums::CUMULATIVE_SCORE)
		{
			os << std::setw(PsilLang::psilVars[i].length() + 2) << g->getCumulativeScore();
		}
		else
		{
			os << std::setw(PsilLang::psilVars[i].length() + 2) << g->getVariable(i);
		}
	}	
	
	for (int i = PsilLang::varEnums::ALLOUTCOMES_A; i <= PsilLang::varEnums::ALLOUTCOMES_C; i++)
	{
		os << std::setw(PsilLang::psilVars[i].length() + 2) << g->getVariable(i);
	}
	os << "\n";
	return os;
}

//Both silent
void Gang::outcomeW()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_W]++;
	mScore += 2;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::W;
	
	//Update the relevant prisoner vars
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->outcomeW();
	}
}

//A silent, B betray
void Gang::outcomeX()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_X]++;
	mScore += 5;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::X;

	//Update the relevant prisoner vars
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->outcomeX();
	}
}

//A betray, B silent
void Gang::outcomeY()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_Y]++;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::Y;

	//Update the relevant prisoner vars
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->outcomeY();
	}
}

//Both betray
void Gang::outcomeZ()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_Z]++;
	mScore += 4;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::Z;

	//Update the relevant prisoner vars
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->outcomeZ();
	}
}

//Mixed, most betrays
void Gang::outcomeA()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_A]++;
	mScore += 2.5;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::A;

	//Update the relevant prisoner vars
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->outcomeA();
	}
}

//Mixed, least betrays
void Gang::outcomeB()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_B]++;
	mScore += 3;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::B;

	//Update the relevant prisoner vars
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->outcomeB();
	}
}

//Mixed, equal
void Gang::outcomeC()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_C]++;
	mScore += 2;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::C;

	//Update the relevant prisoner vars
	for (int i = 0; i < mGangMembers.size(); i++)
	{
		mGangMembers[i]->outcomeC();
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
