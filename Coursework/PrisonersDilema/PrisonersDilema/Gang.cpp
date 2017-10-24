#include "Gang.h"

Gang::Gang()
{
}

Gang::Gang(int id, std::vector<Prisoner*> prisoners)
{
	mID = id;
	for (int i = 0; i < prisoners.size(); i++)
	{
		mPrisoners.push_back(prisoners[i]);
	}

	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::UNKOWN_DECISION;
}

Gang::~Gang()
{
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		delete mPrisoners[i];
	}
}

void Gang::softReset()
{
	for (int i = 0; i < PsilLang::varEnums::UNKOWN_DECISION; i++)
	{
		mVariables[i] = 0;
	}

	for (int i = 0; i < mPrisoners.size(); i++)
	{
		mPrisoners[i]->softReset();
	}
}

void Gang::hardReset()
{
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		mPrisoners[i]->hardReset();
	}

	for (int i = 0; i < PsilLang::varEnums::CUMULATIVE_SCORE; i++)
	{
		mVariables[i] = 0;
	}
}

std::ostream& operator<<(std::ostream& os, const Gang* g)
{
	std::ostringstream ossID;
	ossID << "Gang " << g->getID();
	os << std::setw(15) << std::left << ossID.str();
	for (int i = PsilLang::varEnums::LASTOUTCOME; i <= PsilLang::varEnums::ALLOUTCOMES_Z; i++)
	{
		//If LASTOUTCOME print the letter, otherwise print int value of the variable
		if (i == PsilLang::varEnums::LASTOUTCOME)
		{
			os << std::setw(PsilLang::psilVars[i].length() + 2) << PsilLang::psilVars[g->getVariable(i)];
		}
		else
		{
			os << std::setw(PsilLang::psilVars[i].length() + 2) << g->getVariable(i);
		}
	}	
	
	for (int i = PsilLang::varEnums::ALLOUTCOMES_A; i <= PsilLang::varEnums::ALLOUTCOMES_C; i++)
	{
		os << std::setw(PsilLang::psilVars[i].length() + 2) << g->getPrisoner(0)->getVariable(i);
	}

	//for (int i = PsilLang::varEnums::LASTOUTCOME; i <= PsilLang::varEnums::ALLOUTCOMES_Z; i++)
	//{
	//	std::cout << std::setw(PsilLang::psilVars[i].length() + 2) << PsilLang::psilVars[i];
	//}

	//for (int i = PsilLang::varEnums::ALLOUTCOMES_A; i <= PsilLang::varEnums::ALLOUTCOMES_C; i++)
	//{
	//	std::cout << std::setw(PsilLang::psilVars[i].length() + 2) << PsilLang::psilVars[i];
	//}
	os << "\n";
	return os;
}

//Both silent
void Gang::outcomeW()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_W]++;
	mVariables[PsilLang::varEnums::MYSCORE] += 2;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::W;
	
	//Update the relevant prisoner vars
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		mPrisoners[i]->outcomeW();
	}
}

//A silent, B betray
void Gang::outcomeX()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_X]++;
	mVariables[PsilLang::varEnums::MYSCORE] += 5;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::X;

	//Update the relevant prisoner vars
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		mPrisoners[i]->outcomeX();
	}
}

//A betray, B silent
void Gang::outcomeY()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_Y]++;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::Y;

	//Update the relevant prisoner vars
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		mPrisoners[i]->outcomeY();
	}
}

//Both betray
void Gang::outcomeZ()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_Z]++;
	mVariables[PsilLang::varEnums::MYSCORE] += 4;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::Z;

	//Update the relevant prisoner vars
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		mPrisoners[i]->outcomeZ();
	}
}

void Gang::outcomeA()
{
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		mPrisoners[i]->outcomeA();
	}
}

void Gang::outcomeB()
{
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		mPrisoners[i]->outcomeB();
	}
}

void Gang::outcomeC()
{
	for (int i = 0; i < mPrisoners.size(); i++)
	{
		mPrisoners[i]->outcomeC();
	}
}
