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
	std::default_random_engine dre{ rd() };
	std::mt19937 randGenerator(dre);

	//random line distribution between 1 and max lines
	std::uniform_int_distribution<int> lineDistribution(1, Language::MAXLINES);

	//Set the number of lines for this strategy
	const int totalLines = lineDistribution(randGenerator);
	//const int totalLines = 1;
	//array of strings with each index representing a line of the strategy
	std::string strategy[Language::MAXLINES];

	//Weightings for IF, BETRAY, SILENCE, RANDOM
	const int NUM_WEIGHTS = 4;
	double weights[NUM_WEIGHTS] = { 4, 1, 1, 1 };
	std::discrete_distribution<int> weightDistribution({ weights[0], weights[1], weights[2], weights[3] });

	//current line number (as an index for arrays) so +1 needed for actual line number starting from 1
	int currentLineNum = 0;
	while (currentLineNum < totalLines)
	{
		//if the program is longer than 1 line then the first line should be an if
		if (currentLineNum == 0 && totalLines > 1)
		{
			weightDistribution = std::discrete_distribution<int>({ weights[0], 0, 0, 0 });
		}

		//last line can't be if
		else if (currentLineNum + 1 >= totalLines)
		{
			weightDistribution = std::discrete_distribution<int>({ 0, weights[1], weights[2], weights[3] });
		}
		
		//otherwise use all defined weights
		else
		{
			weightDistribution = std::discrete_distribution<int>({ weights[0], weights[1], weights[2], weights[3] });
		}
		//Strategy generation logic
		std::ostringstream ossLine;
		ossLine << currentLineNum + 1 << ' ';
		//int cumulativeWeight = 0;
		int randomWord = weightDistribution(randGenerator);
		switch (randomWord)
		{
		case 0: //IF
			ossLine << generateIf(currentLineNum, totalLines, randGenerator);
			strategy[currentLineNum] = ossLine.str();
			lastLine = IF;
			break;
		case 1: //BETRAY
			ossLine << Language::psil_keywords[Language::keywordEnums::BETRAY];
			strategy[currentLineNum] = ossLine.str();
			lastLine = BETRAY;
			break;
		case 2: //SILENCE
			ossLine << Language::psil_keywords[Language::keywordEnums::SILENCE];
			strategy[currentLineNum] = ossLine.str();
			lastLine = SILENCE;
			break;
		case 3: //RANDOM
			ossLine << Language::psil_keywords[Language::keywordEnums::RANDOM];
			strategy[currentLineNum] = ossLine.str();
			lastLine = RANDOM;
			break;
		}

		currentLineNum++;
	}

	FileManager::writeToFile(filePath, totalLines, strategy);
}

//generate a PSIL if statement
std::string StrategyGenerator::generateIf(const int currentLineNum, const int totalLines, std::mt19937 &randGenerator)
{
	//Number of operations on each side (1 or 2)
	bool lhs = false;
	bool rhs = false;

	std::uniform_int_distribution<int> dist(0, 1);

	if (dist(randGenerator) > 0)
	{
		lhs = true;
	}	

	if (dist(randGenerator) > 0)
	{
		rhs = true;
	}

	std::uniform_int_distribution<int> varDistribution(0, Language::varEnums::NO_VAR - 1);

	const int VARS_SIZE = 4;
	int vars[VARS_SIZE];
	for (int i = 0; i < VARS_SIZE; i++)
	{
		vars[i] = varDistribution(randGenerator);
	}

	std::uniform_int_distribution<int> calcOperatorDistribution(Language::operatorEnums::PLUS, Language::operatorEnums::MINUS);
	std::uniform_int_distribution<int> equalityOperatorDistribution(Language::operatorEnums::GREATER_THAN, Language::operatorEnums::EQUALS);

	int equalityOperator = equalityOperatorDistribution(randGenerator);
	int firstOp = calcOperatorDistribution(randGenerator);
	int secondOp = calcOperatorDistribution(randGenerator);

	//Set lhs operator and second var to "" if they aren't being used
	if (!lhs)
	{
		firstOp = Language::operatorEnums::NO_OP;
		vars[1] = Language::varEnums::NO_VAR;
	}
	//Set rhs operator and second var to "" if they aren't being used
	if (!rhs)
	{
		secondOp = Language::operatorEnums::NO_OP;
		vars[3] = Language::varEnums::NO_VAR;
	}

	//GOTO line number should be between (current line + 1) and total lines
	//if on 2nd last line go to last line
	int gotoLine = totalLines;
	if (currentLineNum < totalLines - 2)
	{
		std::uniform_int_distribution<int> gotoDistribution(currentLineNum + 1, totalLines);
		gotoLine = gotoDistribution(randGenerator);
	}

	std::ostringstream ossLine;
	//concatenate the final if statement
	ossLine << Language::psil_keywords[Language::keywordEnums::IF] << Language::psil_vars[vars[0]] << Language::psil_operators[firstOp] 
		<< Language::psil_vars[vars[1]] << Language::psil_operators[equalityOperator] << Language::psil_vars[vars[2]]
		<< Language::psil_operators[secondOp] << Language::psil_vars[vars[3]] << Language::psil_keywords[Language::keywordEnums::GOTO] << gotoLine;

	std::string lineString = ossLine.str();
	return lineString;
}
