#include "prisoner.h"

Prisoner::Prisoner()
{
}

Prisoner::Prisoner(Prisoner* prisoner)
{
	mStrategyName = prisoner->getStrategyName();
	mStrategyPath = prisoner->getStrategyPath();
	mStrategy = prisoner->getStrategy();
	//mVariables[PsilLang::varEnums::CUMULATIVE_SCORE + 1] = { 0 };
}

Prisoner::Prisoner(const std::string& const filePath)
{
	mStrategyPath = filePath;

	//Read the file into the strategy map
	FileManager::readFromFile(mStrategyPath, mStrategy);

	mStrategyName = FileManager::getFileName(filePath);
}

Prisoner::~Prisoner()
{
}

void Prisoner::setStrategy(const std::string& const filePath)
{
	FileManager::readFromFile(filePath, mStrategy);
}

void Prisoner::printStrategy()
{
	for (std::map<int, std::string>::const_iterator it = mStrategy.begin(); it != mStrategy.end(); it++)
	{
		std::cout << it->second << "\n";
	}
}

std::ostream& operator<<(std::ostream& os, const Prisoner* p)
{
	os << std::setw(15) << std::left << p->getStrategyName();
	for (int i = 0; i <= PsilLang::varEnums::ALLOUTCOMES_Z; i++)
	{
		//If LASTOUTCOME print the letter, otherwise print int value of the variable
		if (i == PsilLang::varEnums::LASTOUTCOME)
		{
			os << std::setw(PsilLang::psilVars[i].length() + 2) << PsilLang::psilVars[p->getVariable(i)];
		}
		else
		{
			os << std::setw(PsilLang::psilVars[i].length() + 2) << p->getVariable(i);
		}
	}
	os << "\n";
	return os;
}

void Prisoner::softReset()
{
	for (int i = 0; i < PsilLang::varEnums::C; i++)
	{
		mVariables[i] = 0;
	}
}

void Prisoner::hardReset()
{
	softReset();
	mVariables[PsilLang::varEnums::CUMULATIVE_SCORE] = 0;
}

//Both silent
void Prisoner::outcomeW()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_W]++;
	mVariables[PsilLang::varEnums::MYSCORE] += 2;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::W;
}

//A silent, B betray
void Prisoner::outcomeX()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_X]++;
	mVariables[PsilLang::varEnums::MYSCORE] += 5;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::X;
}

//A betray, B silent
void Prisoner::outcomeY()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_Y]++;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::Y;
}

//Both betray
void Prisoner::outcomeZ()
{
	mVariables[PsilLang::varEnums::ALLOUTCOMES_Z]++;
	mVariables[PsilLang::varEnums::MYSCORE] += 4;
	mVariables[PsilLang::varEnums::LASTOUTCOME] = PsilLang::varEnums::Z;
}
