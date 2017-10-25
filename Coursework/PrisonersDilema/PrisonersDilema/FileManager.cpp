#include "fileManager.h"

void FileManager::readFromFile(const std::string& filePath, std::map<int, std::string>& const strategy)
{
	strategy.erase(strategy.begin(), strategy.end());
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
		std::cout << "Unable to open file\n";
	}
}

void FileManager::writeToFile(const std::string& filePath, const std::map<int, std::string>& const strategy)
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
		std::cout << "Unable to open file\n";
	}
}

void FileManager::writeToFile(const std::string & filePath, const std::string& const s)
{
	std::ofstream file(filePath);
	if (file.is_open())
	{
		file << s;
		file.close();
	}
	else
	{
		std::cout << "Unable to open file\n";
	}
}

//Return the raw file name from a file path
const std::string FileManager::getFileName(const std::string& const filePath)
{
	//Remove folder path
	std::size_t botDirPos = filePath.find_last_of('/');
	std::string temp = filePath.substr(botDirPos + 1, filePath.length());

	//Remove the extension
	std::size_t extensionePos = temp.find_last_of('.');
	return temp.substr(0, extensionePos);
}