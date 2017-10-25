#include "GangMember.h"

GangMember::GangMember()
{
}

GangMember::GangMember(Prisoner* p)
{
	mStrategyName = p->getStrategyName();
	mStrategyPath = p->getStrategyPath();
	mStrategy = p->getStrategy();
	mVariables[PsilLang::varEnums::CUMULATIVE_SCORE + 1] = { 0 };
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::UNKOWN_DECISION;
}

GangMember::GangMember(GangMember* gm)
{
	mStrategyName = gm->getStrategyName();
	mStrategyPath = gm->getStrategyPath();
	mStrategy = gm->getStrategy();
	mVariables[PsilLang::varEnums::CUMULATIVE_SCORE + 1] = { 0 };
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::UNKOWN_DECISION;
}

GangMember::GangMember(const std::string & const folderPath)
{
	mStrategyPath = folderPath;

	//Read the file into the strategy map
	FileManager::readFromFile(mStrategyPath, mStrategy);
	//Remove the path and extension from the strategy name and store it
	mStrategyName = FileManager::getFileName(mStrategyPath);
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::UNKOWN_DECISION;
}

GangMember::~GangMember()
{
}

void GangMember::outcomeA()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_A]++;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::A;
}

void GangMember::outcomeB()
{

	mVariables[PsilLang::varEnums::ALLOUTCOMES_B]++;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::B;
}

void GangMember::outcomeC()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_C]++;
	mVariables[PsilLang::varEnums::MYSCORE] += 2;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::C;
}

std::ostream & operator<<(std::ostream & os, const GangMember* gm)
{
	os << std::setw(15) << std::left << gm->getStrategyName();
	for (int i = 0; i <= PsilLang::varEnums::ALLOUTCOMES_Z; i++)
	{
		//If LASTOUTCOME print the letter, otherwise print int value of the variable
		if (i == PsilLang::varEnums::LASTOUTCOME)
		{
			os << std::setw(PsilLang::psilVars[i].length() + 2) << PsilLang::psilVars[gm->getVariable(i)];
		}
		else
		{
			os << std::setw(PsilLang::psilVars[i].length() + 2) << gm->getVariable(i);
		}
	}
	os << "\n";
	return os;
}
