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

void GangMember::softReset()
{
	Prisoner::softReset();
	mScore = 0.0f;
}

void GangMember::hardReset()
{
	softReset();
	mVariables[PsilLang::varEnums::CUMULATIVE_SCORE] = 0;
	mCumulativeScore = 0.0f;
}

//Both silent
void GangMember::outcomeW()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_W]++;
	mScore += 2;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::W;
}

//A silent, B betray
void GangMember::outcomeX()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_X]++;
	mScore += 5;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::X;
}

//A betray, B silent
void GangMember::outcomeY()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_Y]++;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::Y;
}

//Both betray
void GangMember::outcomeZ()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_Z]++;
	mScore += 4;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::Z;
}

void GangMember::outcomeA()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_A]++;
	mScore += 2.5;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::A;
}

void GangMember::outcomeB()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_B]++;
	mScore += 3;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::B;
}

void GangMember::outcomeC()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_C]++;
	mScore += 2;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::C;
}

std::ostream& operator<<(std::ostream & os, const GangMember* gm)
{
	os << std::setw(15) << std::left << gm->getStrategyName();
	for (int i = 0; i <= PsilLang::varEnums::ALLOUTCOMES_Z; i++)
	{
		//If LASTOUTCOME print the letter, otherwise print int value of the variable
		if (i == PsilLang::varEnums::LASTOUTCOME)
		{
			os << std::setw(PsilLang::psilVars[i].length() + 2) << PsilLang::psilVars[gm->getVariable(i)];
		}
		//If MYSCORE print var as it's stored as a double and not in the array
		else if (i == PsilLang::varEnums::MYSCORE)
		{
			os << std::setw(PsilLang::psilVars[i].length() + 2) << gm->getScore();
		}
		//If CUMULATIVE_SCORE print var as it's stored as a double and not in the array
		else if (i == PsilLang::varEnums::CUMULATIVE_SCORE)
		{
			os << std::setw(PsilLang::psilVars[i].length() + 2) << gm->getCumulativeScore();
		}
		else
		{
			os << std::setw(PsilLang::psilVars[i].length() + 2) << gm->getVariable(i);
		}
	}
	os << "\n";
	return os;
}
