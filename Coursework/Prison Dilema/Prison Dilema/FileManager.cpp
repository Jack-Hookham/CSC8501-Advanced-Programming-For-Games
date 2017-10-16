#include "fileManager.h"

void FileManager::readFileToArray(std::string filePath, std::string lines[])
{
	std::string line;
	std::ifstream file(filePath);

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
		std::cout << "Unable to open file";
	}
}
