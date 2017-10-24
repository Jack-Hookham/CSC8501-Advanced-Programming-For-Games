#include "StrategyGenerator.h"

const std::string StrategyGenerator::prisonerPath = "../Strategies/Generated/Prisoner/";
const std::string StrategyGenerator::gangPath = "../Strategies/Generated/Gang/";

void StrategyGenerator::generate(const int n, const bool gangStrategy, const int lineNumIncrement)
{
	for (int i = 0; i < n; i++)
	{
		//generate strategy number i
		generateStrategy(i + 1, gangStrategy, lineNumIncrement);
	}
}

void StrategyGenerator::generateStrategy(const int pathIndex, const bool gangStrategy, const int lineNumIncrement)
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

	int currentLineIndex = 0;	//Line number by index 0, 1, 2 etc
	int currentLineNum = lineNumIncrement;	//Line number by value to be written to file e.g. 10, 20, 30 etc

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
			ossLine << generateIf(currentLineIndex, lineNumIncrement, totalLines, gangStrategy);
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
		currentLineNum += lineNumIncrement;
	}

	FileManager::writeToFile(filePath, strategy);
}

//generate a PSIL if statement
std::string StrategyGenerator::generateIf(const int currentLineIndex, const int lineNumIncrement, const int totalLines, const bool gangStrategy)
{
	std::vector<int> lhsVars;
	std::vector<int> rhsVars;
	generateVars(lhsVars, rhsVars, gangStrategy);

	int conditionalOperatorEnum;
	std::vector<int> lhsOperatorEnums(lhsVars.size());
	std::vector<int> rhsOperatorEnums(rhsVars.size());
	conditionalOperatorEnum = generateOperators(lhsOperatorEnums, rhsOperatorEnums);

	//If either lhs or rhs var is LASTOUTCOME then conditionalOperator must be equality so overwrite it
	if (lhsVars[0] == PsilLang::varEnums::LASTOUTCOME || rhsVars[0] == PsilLang::varEnums::LASTOUTCOME)
	{
		conditionalOperatorEnum = PsilLang::operatorEnums::EQUALS;
	}

	//GOTO line number should be between (current line + 1) and total lines
	//if on 2nd last line go to last line
	int gotoLine = totalLines * lineNumIncrement;		//default to last line
	//if not 2nd last line choose random line greater than current line
	if (currentLineIndex < totalLines - 1)
	{
		gotoLine = (RandomGen::generateRandomWithinRange(currentLineIndex + 2, totalLines)) * lineNumIncrement;
	}

	std::ostringstream ossLine;
	//Concatenate the final if statement
	ossLine << PsilLang::psilKeywords[PsilLang::keywordEnums::IF] << ' ';

	//Lhs vars and operators
	for (int i = 0; i < lhsVars.size(); i++)
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

		if (i < lhsVars.size() - 1)
		{
			ossLine << PsilLang::psilOperators[lhsOperatorEnums[i]] << ' ';
		}
	}

	//Conditional Operator
	ossLine << PsilLang::psilOperators[conditionalOperatorEnum] << ' ';

	//Rhs vars and operators
	for (int i = 0; i < rhsVars.size(); i++)
	{
		if ((gangStrategy && rhsVars[i] == PsilLang::varEnums::ALLOUTCOMES_C + 1) || (rhsVars[i] == PsilLang::varEnums::ALLOUTCOMES_Z + 1))
		{
			ossLine << intToString(RandomGen::generateRandomWithinRange(INT_VAR_MIN, INT_VAR_MAX)) << ' ';
		}
		else
		{
			ossLine << PsilLang::psilVars[rhsVars[i]] << ' ';
		}
		if (i < rhsVars.size() - 1)
		{
			ossLine << PsilLang::psilOperators[rhsOperatorEnums[i]] << ' ';
		}
	}
	
	ossLine << PsilLang::psilKeywords[PsilLang::keywordEnums::GOTO] << ' ' << gotoLine;

	std::string lineString = ossLine.str();
	return lineString;
}

void StrategyGenerator::generateVars(std::vector<int>& lhsVars, std::vector<int>& rhsVars, const bool gangStrategy)
{
	//Store upperbounds for random number gen which will vary based on the gangStrategy bool
	int varGenUpperBound;
	int wxyzabcUpperBound;

	if (gangStrategy)
	{
		varGenUpperBound = PsilLang::varEnums::INTEGER_PLACEHOLDER_2;
		wxyzabcUpperBound = PsilLang::varEnums::C;
	}
	else
	{
		varGenUpperBound = PsilLang::varEnums::INTEGER_PLACEHOLDER_1;
		wxyzabcUpperBound = PsilLang::varEnums::Z;
	}
	//Chance of 1, 2 or 3 variables on each side of the equation
	std::vector<double> numVarsWeights = { 4, 2, 1 };

	//Number of variables for lhs and rhs of equations
	int numLhsVars = RandomGen::generateRandomWeighted(numVarsWeights) + 1;
	int numRhsVars = RandomGen::generateRandomWeighted(numVarsWeights) + 1;

	//First vars for both sides
	lhsVars.push_back(RandomGen::generateRandomWithinRange(PsilLang::varEnums::LASTOUTCOME, varGenUpperBound));
	rhsVars.push_back(RandomGen::generateRandomWithinRange(PsilLang::varEnums::LASTOUTCOME, varGenUpperBound));

	//if first variable is LASTOUTCOME it must be compared with w, x, y, z instead of the other variables and operator must be EQUALS
	if (lhsVars[0] == PsilLang::varEnums::LASTOUTCOME)
	{
		//set the other side of the equation to w, x, y or z (a, b, c included if strategy is for a gang prisoner)
		rhsVars[0] = RandomGen::generateRandomWithinRange(PsilLang::varEnums::W, wxyzabcUpperBound);
		numLhsVars = 1;
		numRhsVars = 1;
	}
	else if (rhsVars[0] == PsilLang::varEnums::LASTOUTCOME)
	{
		lhsVars[0] = RandomGen::generateRandomWithinRange(PsilLang::varEnums::W, wxyzabcUpperBound);
		numLhsVars = 1;
		numRhsVars = 1;
	}
	//else continue with random variable generation
	else
	{
		//Populate the rest of the lhs and rhs vars
		for (int i = 1; i < numLhsVars; i++)
		{
			lhsVars.push_back(RandomGen::generateRandomWithinRange(PsilLang::varEnums::ALLOUTCOMES_W, varGenUpperBound));
		}

		for (int i = 1; i < numRhsVars; i++)
		{
			rhsVars.push_back(RandomGen::generateRandomWithinRange(PsilLang::varEnums::ALLOUTCOMES_W, varGenUpperBound));
		}
	}
}

const int StrategyGenerator::generateOperators(std::vector<int>& lhsOps, std::vector<int>& rhsOps)
{
	//Populate lhs and rhs operators
	for (int i = 0; i < lhsOps.size() - 1; i++)
	{
		lhsOps[i] = (RandomGen::generateRandomWithinRange(PsilLang::operatorEnums::PLUS, PsilLang::operatorEnums::MINUS));
	}

	for (int i = 0; i < rhsOps.size() - 1; i++)
	{
		rhsOps[i] = (RandomGen::generateRandomWithinRange(PsilLang::operatorEnums::PLUS, PsilLang::operatorEnums::MINUS));
	}

	return RandomGen::generateRandomWithinRange(PsilLang::operatorEnums::GREATER_THAN, PsilLang::operatorEnums::EQUALS);
}



std::string StrategyGenerator::intToString(const int x)
{
	std::ostringstream oss;
	oss << x;
	return oss.str();
}