#include "prisoner.h"

Prisoner::Prisoner()
{
}

Prisoner::Prisoner(std::string filePath)
{
	FileManager::readFromFile(filePath, mStrategy);
}

Prisoner::~Prisoner()
{
}

void Prisoner::setStrategy(std::string filePath)
{
	FileManager::readFromFile(filePath, mStrategy);
}

void Prisoner::print()
{
	for (std::map<int, std::string>::const_iterator it = mStrategy.begin(); it != mStrategy.end(); it++)
	{
		std::cout << it->second << "\n";
	}
}
