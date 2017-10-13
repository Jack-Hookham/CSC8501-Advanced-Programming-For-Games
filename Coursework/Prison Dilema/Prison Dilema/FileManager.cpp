#include "fileManager.h"

void FileManager::readFileToArray(string filePath, string lines[])
{
	string line;
	ifstream file(filePath);

	if (file.is_open())
	{
		int currentLineIndex = 0;
		while (getline(file, line))
		{
			lines[currentLineIndex] = line + "\n";
			currentLineIndex++;
		}
		file.close();
	}
	else
	{
		cout << "Unable to open file";
	}
}
