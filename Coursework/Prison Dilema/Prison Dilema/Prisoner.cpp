#include "Prisoner.h"

Prisoner::Prisoner(string strategyPath)
{
	FileManager::readFileToArray(strategyPath, strategyLines);

	cout << "done";
}

Prisoner::~Prisoner()
{
}

void Prisoner::print()
{
	for (int i = 0; i < MAX_LINES; i++)
	{
		cout << strategyLines[i];
	}
}
