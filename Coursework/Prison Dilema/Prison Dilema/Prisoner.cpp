#include "Prisoner.h"

Prisoner::Prisoner(std::string strategyPath)
{
	FileManager::readFromFile(strategyPath, strategyLines);
}

Prisoner::~Prisoner()
{
}

void Prisoner::print()
{
	for (int i = 0; i < Language::MAXLINES; i++)
	{
		std::cout << strategyLines[i];
	}
}
