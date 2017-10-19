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
	for (int i = 0; i < Language::MAX_READ_LINES; i++)
	{
		std::cout << strategy[i];
	}
}
