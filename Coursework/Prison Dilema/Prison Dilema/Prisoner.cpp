#include "Prisoner.h"

Prisoner::Prisoner(std::string filePath)
{
	FileManager::readFromFile(filePath, strategy);
}

Prisoner::~Prisoner()
{
}

void Prisoner::print()
{
	for (int i = 0; i < strategy.size(); i++)
	{
		std::cout << strategy[i];
	}
}
