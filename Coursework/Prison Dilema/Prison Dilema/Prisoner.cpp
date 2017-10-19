#include "Prisoner.h"

Prisoner::Prisoner()
{
}

Prisoner::Prisoner(std::string filePath)
{
	FileManager::readFromFile(filePath, strategy);
}

Prisoner::~Prisoner()
{
}

void Prisoner::setStrategy(std::string filePath)
{
	FileManager::readFromFile(filePath, strategy);
}

void Prisoner::print()
{
	//for (int i = 0; i < arraySize(strategy); i++)
	for (std::map<int, std::string>::const_iterator it = strategy.begin(); it != strategy.end(); it++)
	{
		std::cout << it->second << "\n";
	}
}
