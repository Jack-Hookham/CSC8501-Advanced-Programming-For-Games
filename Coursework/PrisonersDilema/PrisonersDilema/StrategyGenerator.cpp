#include "StrategyGenerator.h"

const std::string StrategyGenerator::prisonerPath = "../Strategies/Generated/Prisoner/";
const std::string StrategyGenerator::gangPath = "../Strategies/Generated/Gang/";

void StrategyGenerator::generate(const int n, const bool gangStrategy)
{
	for (int i = 0; i < n; i++)
	{
		//generate strategy number i
		generateStrategy(i + 1, gangStrategy);
	}
}

void StrategyGenerator::generateStrategy(const int pathIndex, const bool gangStrategy)
{
	//Map of line numbers and line strings
	std::map<int, std::string> strategy;

	//Generate the file path
	std::string folderPath;
	if (gangStrategy)
	{
		folderPath = gangPath;
	}
	else
	{
		folderPath = prisonerPath;
	}

	std::ostringstream ossPath;
	ossPath << folderPath << "Strategy" << pathIndex << ".txt";
	std::string filePath = ossPath.str();

	//random total line number distribution between 1 and max lines
	//Set the number of lines for this strategy
	const int totalLines = RandomGen::generateRandomWithinRange(1, PsilLang::MAX_WRITE_LINES);

	//current line index so +1 needed for actual line number starting from 1
	int currentLineIndex = 0;

	//Current value used for line number in the strategy
	int currentLineNum = 10;

	while (currentLineIndex < totalLines)
	{
		//Weightings for IF, BETRAY, SILENCE, RANDOM
		std::vector<double> lineTypeWeights = { 4.0, 1.0, 1.0, 1.0 };

		//Strategy generation logic
		//if the program is longer than 1 line then the first line should be an if
		if (currentLineIndex == 0 && totalLines > 1)
		{
			//Set all weightings to 0 except IF
			lineTypeWeights = { lineTypeWeights[0], 0, 0, 0 };
		}

		//if > 3 lines then last 2 lines can't be if
		else if (currentLineIndex >= totalLines - 2)
		{
			lineTypeWeights = { 0, lineTypeWeights[1], lineTypeWeights[2], lineTypeWeights[3] };
		}

		std::ostringstream ossLine;
		ossLine << currentLineNum << ' ';
		int randomWord = RandomGen::generateRandomWeighted(lineTypeWeights);
		switch (randomWord)
		{
		case 0: //IF
			ossLine << generateIf(currentLineIndex, totalLines, gangStrategy);
			strategy.insert(std::pair<int, std::string>(currentLineNum, ossLine.str()));
			break;
		case 1: //BETRAY
			ossLine << PsilLang::psilKeywords[PsilLang::keywordEnums::BETRAY];
			strategy.insert(std::pair<int, std::string>(currentLineNum, ossLine.str()));
			break;
		case 2: //SILENCE
			ossLine << PsilLang::psilKeywords[PsilLang::keywordEnums::SILENCE];
			strategy.insert(std::pair<int, std::string>(currentLineNum, ossLine.str()));
			break;
		case 3: //RANDOM
			ossLine << PsilLang::psilKeywords[PsilLang::keywordEnums::RANDOM];
			strategy.insert(std::pair<int, std::string>(currentLineNum, ossLine.str()));
			break;
		}

		currentLineIndex++;
		currentLineNum += 10;
	}

	FileManager::writeToFile(filePath, strategy);
}

//generate a PSIL if statement
std::string StrategyGenerator::generateIf(const int currentLineIndex, const int totalLines, const bool gangStrategy)
{
	//Number of operations on each side (1 or 2)
	int lhs = false;
	bool rhs = false;

	//Chance of 1, 2 or 3 variables on each side of the equation
	std::vector<double> numVarsWeights = { 4, 2, 1 };

	//Number of variables for lhs and rhs of equations
	int numLhsVars = RandomGen::generateRandomWeighted(numVarsWeights) + 1;
	int numRhsVars = RandomGen::generateRandomWeighted(numVarsWeights) + 1;

	//Store temporary upperbounds for random number gen which will vary based on the gangStrategy bool
	int upperBound;

	//For varDistribution ENUM + 1 represents a random number that will need to be generated
	std::uniform_int_distribution<int> varDistribution;
	if (gangStrategy)
	{
		upperBound = PsilLang::varEnums::INTEGER_PLACEHOLDER_2;
	}
	else
	{
		upperBound = PsilLang::varEnums::INTEGER_PLACEHOLDER_1;
	}

	std::vector<int> lhsVars;
	std::vector<int> rhsVars;

	//First vars for both sides
	lhsVars.push_back(RandomGen::generateRandomWithinRange(PsilLang::varEnums::LASTOUTCOME, upperBound));
	rhsVars.push_back(RandomGen::generateRandomWithinRange(PsilLang::varEnums::LASTOUTCOME, upperBound));

	int conditionalOperatorEnum;
	std::vector<int> lhsOperatorEnums;
	std::vector<int> rhsOperatorEnums;

	//if first variable is LASTOUTCOME it must be compared with w, x, y, z instead of the other variables and operator must be EQUALS
	if (lhsVars[0] == PsilLang::varEnums::LASTOUTCOME)
	{
		conditionalOperatorEnum = PsilLang::operatorEnums::EQUALS;
		if (gangStrategy)
		{
			upperBound = PsilLang::varEnums::C;
		}
		else
		{
			upperBound = PsilLang::varEnums::Z;
		}
		//set the other side of the equation to w, x, y or z (a, b, c included if strategy is for a gang prisoner)
		rhsVars[0] = RandomGen::generateRandomWithinRange(PsilLang::varEnums::W, upperBound);
		numLhsVars = 1;
		numRhsVars = 1;
	}
	else if (rhsVars[0] == PsilLang::varEnums::LASTOUTCOME)
	{
		conditionalOperatorEnum = PsilLang::operatorEnums::EQUALS;
		std::uniform_int_distribution<int> wxyzDist;
		if (gangStrategy)
		{
			upperBound = PsilLang::varEnums::C;
		}
		else
		{
			upperBound = PsilLang::varEnums::Z;
		}
		lhsVars[0] = RandomGen::generateRandomWithinRange(PsilLang::varEnums::W, upperBound);
		numLhsVars = 1;
		numRhsVars = 1;
	}
	//else continue with random variable generation
	else
	{
		//Remove LASTOUTCOME from possible vars
		if (gangStrategy)
		{
			upperBound = PsilLang::varEnums::INTEGER_PLACEHOLDER_2;
		}
		else
		{
			upperBound = PsilLang::varEnums::INTEGER_PLACEHOLDER_1;
		}

		//Populate the rest of the lhs and rhs vars
		for (int i = 1; i < numLhsVars; i++)
		{
			lhsVars.push_back(RandomGen::generateRandomWithinRange(PsilLang::varEnums::ALLOUTCOMES_W, upperBound));
		}

		for (int i = 1; i < numRhsVars; i++)
		{
			rhsVars.push_back(RandomGen::generateRandomWithinRange(PsilLang::varEnums::ALLOUTCOMES_W, upperBound));
		}

		conditionalOperatorEnum = RandomGen::generateRandomWithinRange(PsilLang::operatorEnums::GREATER_THAN, PsilLang::operatorEnums::EQUALS);

		//Populate lhs and rhs operators
		for (int i = 0; i < numLhsVars - 1; i++)
		{
			lhsOperatorEnums.push_back(RandomGen::generateRandomWithinRange(PsilLang::operatorEnums::PLUS, PsilLang::operatorEnums::MINUS));
		}

		for (int i = 0; i < numRhsVars - 1; i++)
		{
			rhsOperatorEnums.push_back(RandomGen::generateRandomWithinRange(PsilLang::operatorEnums::PLUS, PsilLang::operatorEnums::MINUS));
		}
	}

	//GOTO line number should be between (current line + 1) and total lines
	//if on 2nd last line go to last line
	int gotoLine = totalLines * 10;		//default to last line
	//if not 2nd last line choose random line greater than current line
	if (currentLineIndex < totalLines - 1)
	{
		gotoLine = (RandomGen::generateRandomWithinRange(currentLineIndex + 2, totalLines)) * 10;
	}

	std::ostringstream ossLine;
	//Concatenate the final if statement
	ossLine << PsilLang::psilKeywords[PsilLang::keywordEnums::IF] << ' ';

	//Lhs vars and operators
	for (int i = 0; i < numLhsVars; i++)
	{
		//if the current variable is an integer value then generate that value
		//else just used the string represented by the value
		if ((gangStrategy && lhsVars[i] == PsilLang::varEnums::INTEGER_PLACEHOLDER_2) || (lhsVars[i] == PsilLang::varEnums::INTEGER_PLACEHOLDER_1))
		{
			ossLine << intToString(RandomGen::generateRandomWithinRange(INT_VAR_MIN, INT_VAR_MAX)) << ' ';
		}
		else
		{
			ossLine << PsilLang::psilVars[lhsVars[i]] << ' ';
		}

		if (i < numLhsVars - 1)
		{
			ossLine << PsilLang::psilOperators[lhsOperatorEnums[i]] << ' ';
		}
	}

	//Conditional Operator
	ossLine << PsilLang::psilOperators[conditionalOperatorEnum] << ' ';

	//Rhs vars and operators
	for (int i = 0; i < numRhsVars; i++)
	{
		if ((gangStrategy && rhsVars[i] == PsilLang::varEnums::ALLOUTCOMES_C + 1) || (rhsVars[i] == PsilLang::varEnums::ALLOUTCOMES_Z + 1))
		{
			ossLine << intToString(RandomGen::generateRandomWithinRange(INT_VAR_MIN, INT_VAR_MAX)) << ' ';
		}
		else
		{
			ossLine << PsilLang::psilVars[rhsVars[i]] << ' ';
		}
		if (i < numRhsVars - 1)
		{
			ossLine << PsilLang::psilOperators[rhsOperatorEnums[i]] << ' ';
		}
	}
	
	ossLine << PsilLang::psilKeywords[PsilLang::keywordEnums::GOTO] << ' ' << gotoLine;

	std::string lineString = ossLine.str();
	return lineString;
}

std::string StrategyGenerator::intToString(const int x)
{
	std::ostringstream oss;
	oss << x;
	return oss.str();
}
