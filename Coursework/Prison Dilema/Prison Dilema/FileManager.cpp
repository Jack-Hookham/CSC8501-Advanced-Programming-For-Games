#include "fileManager.h"

void FileManager::readFromFile(std::string filePath, std::vector<std::string>& strategy)
{
	std::string line;
	std::ifstream file(filePath);

	if (file.is_open())
	{
		int currentLineIndex = 0;
		while (getline(file, line))
		{
			strategy.push_back(line + "\n");
			currentLineIndex++;
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
}

void FileManager::writeToFile(std::string filePath, int lines, std::vector<std::string>& strategy)
{
	std::ofstream file(filePath);
	if (file.is_open())
	{
		for (int i = 0; i < lines; i++)
		{
			file << strategy[i] << "\n";
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
}
