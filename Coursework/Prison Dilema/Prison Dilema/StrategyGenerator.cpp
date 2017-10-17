#include "StrategyGenerator.h"

void StrategyGenerator::generate(int n)
{
	for (int i = 0; i < n; i++)
	{
		//generate strategy number i
		generateStrategy(i);
	}
}

void StrategyGenerator::generateStrategy(const int index)
{
	//enum used to keep track of the type for the last line
	enum lineEnum
	{
		IF,
		BETRAY,
		SILENCE,
		RANDOM,
		START
	};

	int lastLine = lineEnum::START;

	std::ostringstream ossPath;
	ossPath << "../Strategies/WriteTest" << index << ".txt";
	std::string filePath = ossPath.str();

	std::mt19937 randGenerator(time(0));
	//random line distribution between 1 and max lines
	std::uniform_int_distribution<int> lineDistribution(1, Language::MAXLINES);

	//Set the number of lines for this strategy
	const int lines = lineDistribution(randGenerator);

	//array of strings with each index representing a line of the strategy
	std::string strategy[Language::MAXLINES];
	
	const int NUM_WEIGHTS = 4;
	int weights[NUM_WEIGHTS] = { 70, 10, 10, 10 };
	int totalWeight = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++)
	{
		totalWeight += weights[i];
	}

	std::uniform_int_distribution<int> weightDistribution(0, totalWeight - 1);

	int lineNumber = 0;
	while (lineNumber < Language::MAXLINES)
	{
		//if the number of lines has been reached stop adding lines
		if (lineNumber >= lines)
		{
			break;
		}
		//strategy generation logic
		else
		{
			//START LINE
			int cumulativeWeight = 0;
			int weight = weightDistribution(randGenerator);
			
			for (int i = 0; i < NUM_WEIGHTS; i++)
			{
				cumulativeWeight += weights[i];
				if (weight < cumulativeWeight)
				{
					std::ostringstream ossLine;
					ossLine << lineNumber + 1 << ' ';
					switch (i)
					{
					case 0: //IF
						ossLine << generateIf();
						strategy[lineNumber] = ossLine.str();														
						break;
					case 1: //BETRAY
						ossLine << Language::keywords[Language::keywordsEnum::BETRAY];
						strategy[lineNumber] = ossLine.str();
						break;
					case 2: //SILENCE
						ossLine << Language::keywords[Language::keywordsEnum::SILENCE];
						strategy[lineNumber] = ossLine.str();
						break;
					case 3: //RANDOM
						ossLine << Language::keywords[Language::keywordsEnum::RANDOM];
						strategy[lineNumber] = ossLine.str();
						break;
					}
				}
			}
		}

		lineNumber++;
	}


	FileManager::writeToFile(filePath, lines, strategy);
}

//generate a PSIL if statement
std::string StrategyGenerator::generateIf()
{
	std::string lineString;



	return lineString;
}
