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

	std::random_device rd;
	std::mt19937 randGenerator(rd());
	//random line distribution between 1 and max lines
	std::uniform_int_distribution<int> lineDistribution(1, Language::MAXLINES);

	std::uniform_int_distribution<int> firstVarDistribution(0, Language::varEnums::NUM_VARS - 1);
	std::uniform_int_distribution<int> secondVarDistribution(0, Language::varEnums::NUM_VARS - 2);

	//-2 to exclude =
	std::uniform_int_distribution<int> operatorDistribution(0, Language::operatorEnums::NUM_OPERATORS - 2);

	//Set the number of lines for this strategy
	const int totalLines = lineDistribution(randGenerator);

	//array of strings with each index representing a line of the strategy
	std::string strategy[Language::MAXLINES];
	
	const int NUM_WEIGHTS = 4;
	//IF, BETRAY, SILENCE, RANDOM keyword weightings
	//DISCRETE DIST???
	int weights[NUM_WEIGHTS] = { 70, 10, 10, 10 };
	int totalWeight = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++)
	{
		totalWeight += weights[i];
	}

	std::uniform_int_distribution<int> weightDistribution(0, totalWeight - 1);

	int currentLineNum = 0;
	while (currentLineNum <= Language::MAXLINES)
	{
		//if the number of lines has been reached stop adding lines
		if (currentLineNum >= totalLines)
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
					ossLine << currentLineNum + 1 << ' ';
					switch (i)
					{
					case 0: //IF
						ossLine << generateIf(currentLineNum, totalLines, randGenerator, firstVarDistribution, secondVarDistribution, operatorDistribution);
						strategy[currentLineNum] = ossLine.str();
						i = NUM_WEIGHTS; 
						lastLine = IF;
						break;
					case 1: //BETRAY
						ossLine << Language::psil_keywords[Language::keywordEnums::BETRAY];
						strategy[currentLineNum] = ossLine.str();
						i = NUM_WEIGHTS;
						lastLine = BETRAY;
						break;
					case 2: //SILENCE
						ossLine << Language::psil_keywords[Language::keywordEnums::SILENCE];
						strategy[currentLineNum] = ossLine.str();
						i = NUM_WEIGHTS;
						lastLine = SILENCE;
						break;
					case 3: //RANDOM
						ossLine << Language::psil_keywords[Language::keywordEnums::RANDOM];
						strategy[currentLineNum] = ossLine.str();
						i = NUM_WEIGHTS;
						lastLine = RANDOM;
						break;
					}
				}
			}
		}

		currentLineNum++;
	}

	FileManager::writeToFile(filePath, totalLines, strategy);
}

//generate a PSIL if statement
std::string StrategyGenerator::generateIf(const int currentLineNum, const int totalLines, std::mt19937 &randGenerator,
	std::uniform_int_distribution<int> &firstVarDistribution, std::uniform_int_distribution<int> &secondVarDistribution, 
	std::uniform_int_distribution<int> &operatorDistribution)
{

	int firstVar = firstVarDistribution(randGenerator);
	int secondVar = secondVarDistribution(randGenerator);

	//greatest enum is removed from secondVarDistribution
	//if the same variables are picked then second var is set to greatest enum
	if (firstVar == secondVar)
	{
		secondVar = Language::varEnums::MYSCORE;
	}

	int op = operatorDistribution(randGenerator);

	//GOTO line number should be between (current line + 1) and total lines
	std::uniform_int_distribution<int> gotoDistribution(currentLineNum + 1, totalLines);
	int gotoLine = gotoDistribution(randGenerator);

	std::ostringstream ossLine;
	//concatenate the final if statement
	ossLine << "IF " << Language::psil_vars[firstVar] << ' ' << Language::psil_operators[op] << ' ' << Language::psil_vars[secondVar] << " GOTO " << gotoLine;

	std::string lineString = ossLine.str();
	return lineString;
}
