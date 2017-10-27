#include "prisoner.h"

Prisoner::Prisoner()
{
}

Prisoner::Prisoner(Prisoner* prisoner)
{
	mStrategyName = prisoner->getStrategyName();
	mStrategyPath = prisoner->getStrategyPath();
	mStrategy = prisoner->getStrategy();
	mVariables[PsiLang::varEnums::CUMULATIVE_SCORE + 1] = { 0 };
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::UNKOWN_DECISION;
}

Prisoner::Prisoner(const std::string& folderPath)
{
	mStrategyPath = folderPath;

	//Read the file into the strategy map
	try
	{
		FileManager::readFromFile(mStrategyPath, mStrategy);
	}
	catch (const std::invalid_argument& iae)
	{
		std::cout << "Invalid argument: " << iae.what() << "\n";
		exit(1);
	}
	//Remove the path and extension from the strategy name and store it
	mStrategyName = FileManager::getFileName(mStrategyPath);
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::UNKOWN_DECISION;
}

Prisoner::~Prisoner()
{
}

void Prisoner::setStrategy(const std::string& filePath)
{
	mStrategyPath = filePath;
	try
	{
		FileManager::readFromFile(mStrategyPath, mStrategy);
	}
	catch (const std::invalid_argument& iae)
	{
		std::cout << "Invalid argument: " << iae.what() << "\n";
		exit(1);
	}
	mStrategyName = FileManager::getFileName(mStrategyPath);
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
	for (int i = 0; i <= PsiLang::varEnums::ALLOUTCOMES_Z; i++)
	{
		//If LASTOUTCOME print the letter, otherwise print int value of the variable
		if (i == PsiLang::varEnums::LASTOUTCOME)
		{
			os << std::setw(PsiLang::psilVars[i].length() + 2) << PsiLang::psilVars[p->getVariable(i)];
		}
		else
		{
			os << std::setw(PsiLang::psilVars[i].length() + 2) << p->getVariable(i);
		}
	}
	os << "\n";
	return os;
}

void Prisoner::softReset()
{
	for (int i = 0; i < PsiLang::varEnums::UNKOWN_DECISION; i++)
	{
		mVariables[i] = 0;
	}
}

void Prisoner::hardReset()
{
	softReset();
	mVariables[PsiLang::varEnums::CUMULATIVE_SCORE] = 0;
}

//Both silent
void Prisoner::outcomeW()
{
	mVariables[PsiLang::varEnums::ALLOUTCOMES_W]++;
	mVariables[PsiLang::varEnums::MYSCORE] += 2;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::W;
}

//A silent, B betray
void Prisoner::outcomeX()
{
	mVariables[PsiLang::varEnums::ALLOUTCOMES_X]++;
	mVariables[PsiLang::varEnums::MYSCORE] += 5;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::X;
}

//A betray, B silent
void Prisoner::outcomeY()
{
	mVariables[PsiLang::varEnums::ALLOUTCOMES_Y]++;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::Y;
}

//Both betray
void Prisoner::outcomeZ()
{
	mVariables[PsiLang::varEnums::ALLOUTCOMES_Z]++;
	mVariables[PsiLang::varEnums::MYSCORE] += 4;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::Z;
}