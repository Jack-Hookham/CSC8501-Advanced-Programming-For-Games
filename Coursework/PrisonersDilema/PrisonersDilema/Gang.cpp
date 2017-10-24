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
}

void Gang::hardReset()
{
}

std::ostream& operator<<(std::ostream& os, const Gang* g)
{
	os << "Gang" << g->getID() << "\n";

	for (int i = 0; i < g->getPrisoners().size(); i++)
	{
		os << std::setw(15) << std::left << g->getPrisoner(i)->getStrategyName();
		for (int j = 0; j <= PsilLang::varEnums::ALLOUTCOMES_Z; j++)
		{
			//If LASTOUTCOME print the letter, otherwise print int value of the variable
			if (j == PsilLang::varEnums::LASTOUTCOME)
			{
				os << std::setw(10) << PsilLang::psilVars[g->getPrisoner(i)->getVariable(j)];
			}
			else
			{
				os << std::setw(10) << g->getPrisoner(i)->getVariable(j);
			}
		}
		os << "\n";
	}
	return os;
}
