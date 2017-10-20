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
			std::string firstWord = line.substr(0, line.find(" "));

			//Check whether first word of line is an integer
			if (!PsilLang::isInteger(firstWord))
			{
				std::cout << "Invalid file! No line number found.\n";
			}
			else
			{
				//Insert line into the map with line number as the key
				strategy.insert(std::pair<int, std::string>(stoi(firstWord), line));
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
			//Add each line string to the file
			file << it->second << "\n";
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
}
