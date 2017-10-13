#include "Prisoner.h"

Prisoner::Prisoner(string strategyPath)
{
	//strategyLines[MAX_LINES];

	string line;
	ifstream file(strategyPath);

	if (file.is_open())
	{
		int currentLineIndex = 0;
		while (getline(file, line))
		{
			strategyLines[currentLineIndex] = line + "\n";
			currentLineIndex++;
		}
		file.close();
	}
	else
	{
		cout << "Unable to open file";
	}
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
