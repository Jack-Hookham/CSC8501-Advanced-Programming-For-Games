#include "Prisoner.h"

Prisoner::Prisoner(std::string strategyPath)
{
	FileManager::readFileToArray(strategyPath, strategyLines);
}

Prisoner::~Prisoner()
{
}

void Prisoner::print()
{
	for (int i = 0; i < MAX_LINES; i++)
	{
		std::cout << strategyLines[i];
	}
}
