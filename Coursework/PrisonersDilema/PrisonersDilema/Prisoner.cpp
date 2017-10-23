#include "prisoner.h"

Prisoner::Prisoner()
{
}

Prisoner::Prisoner(const std::string filePath)
{
	mStrategyPath = filePath;

	//Read the file into the strategy map
	FileManager::readFromFile(mStrategyPath, mStrategy);

	mStrategyName = FileManager::getFileName(filePath);
}

Prisoner::~Prisoner()
{
}

void Prisoner::setStrategy(const std::string filePath)
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

void Prisoner::printVariables()
{
	std::cout << mStrategyName << "\t";
	for (int i = 0; i <= PsilLang::varEnums::MYSCORE; i++)
	{
		//If LASTOUTCOME print the letter, otherwise print int value of the variable
		if (i == PsilLang::varEnums::LASTOUTCOME)
		{
			std::cout << PsilLang::psilVars[mVariables[i]] << "\t\t";
		}
		else
		{
			std::cout << mVariables[i] << "\t\t";
		}
	}
	std::cout << "\n";
}

void Prisoner::softReset()
{
	for (int i = 0; i <= PsilLang::varEnums::MYSCORE; i++)
	{
		mVariables[i] = 0;
	}
}

void Prisoner::hardReset()
{
	for (int i = 0; i <= PsilLang::varEnums::CUMULATIVE_SCORE; i++)
	{
		mVariables[i] = 0;
	}
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
