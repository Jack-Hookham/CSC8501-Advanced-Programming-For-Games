#include "fileManager.h"

void FileManager::readFromFile(const std::string& filePath, std::map<int, std::string>& strategy)
{
	std::string line;
	std::ifstream file(filePath);

	if (file.is_open())
	{
		int currentLineNumber = 1;
		while (getline(file, line))
		{
			int lineNumber;
			std::string firstWord = line.substr(0, line.find(" "));

			//Check whether first word of line is an integer
			if (!Language::isInteger(firstWord))
			{
				std::cout << "Invalid file! No line number found.\n";
			}
			else
			{
				lineNumber = stoi(firstWord);
				strategy.insert(std::pair<int, std::string>(lineNumber, line));
			}
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
}

void FileManager::writeToFile(const std::string& filePath, const std::map<int, std::string>& strategy)
{
	std::ofstream file(filePath);
	if (file.is_open())
	{
		for (std::map<int, std::string>::const_iterator it = strategy.begin(); it != strategy.end(); it++)
		{
			file << it->second << "\n";
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
}
