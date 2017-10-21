#include "StrategyGenerator.h"

//TODO: Lastoutcome equality only with W, X, Y, Z

void StrategyGenerator::generate(int n)
{
	for (int i = 0; i < n; i++)
	{
		//generate strategy number i
		generateStrategy(i);
	}
}

void StrategyGenerator::generateStrategy(const int pathIndex)
{
	//Map of line numbers and line strings
	std::map<int, std::string> strategy;

	//Generate the file path
	std::ostringstream ossPath;
	ossPath << "../Strategies/WriteTest" << pathIndex << ".txt";
	std::string filePath = ossPath.str();

	std::random_device rd;
	std::default_random_engine dre{ rd() };
	std::mt19937 randGenerator(dre);

	//random line distribution between 1 and max lines
	std::uniform_int_distribution<int> lineDistribution(1, PsilLang::MAX_WRITE_LINES);

	//Set the number of lines for this strategy
	const int totalLines = lineDistribution(randGenerator);

	//Weightings for IF, BETRAY, SILENCE, RANDOM
	const int NUM_WEIGHTS = 4;
	double weights[NUM_WEIGHTS] = { 4, 1, 1, 1 };
	std::discrete_distribution<int> weightDistribution({ weights[0], weights[1], weights[2], weights[3] });

	//current line index so +1 needed for actual line number starting from 1
	int currentLineIndex = 0;

	//Current value used for line number in the strategy
	int currentLineNum = 10;

	while (currentLineIndex < totalLines)
	{
		//Strategy generation logic
		//if the program is longer than 1 line then the first line should be an if
		if (currentLineIndex == 0 && totalLines > 1)
		{
			//Set all weightings to 0 except IF
			weightDistribution = std::discrete_distribution<int>({ weights[0], 0, 0, 0 });
		}

		//if > 3 lines then last 2 lines can't be if
		else if (currentLineIndex >= totalLines - 2)
		{
			weightDistribution = std::discrete_distribution<int>({ 0, weights[1], weights[2], weights[3] });
		}
		
		//otherwise use all defined weights
		else
		{
			weightDistribution = std::discrete_distribution<int>({ weights[0], weights[1], weights[2], weights[3] });
		}

		std::ostringstream ossLine;
		ossLine << currentLineNum << ' ';
		//int cumulativeWeight = 0;
		int randomWord = weightDistribution(randGenerator);
		switch (randomWord)
		{
		case 0: //IF
			ossLine << generateIf(currentLineIndex, totalLines, randGenerator);
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
std::string StrategyGenerator::generateIf(const int currentLineIndex, const int totalLines, std::mt19937 &randGenerator)
{
	//Number of operations on each side (1 or 2)
	int lhs = false;
	bool rhs = false;

	//Chance of 1, 2 or 3 variables on each side of the equation
	std::discrete_distribution<int> numVariablesDistribution( { 4, 2, 1 } );

	//Number of variables for lhs and rhs of equations
	int numLhsVars = numVariablesDistribution(randGenerator) + 1;
	int numRhsVars = numVariablesDistribution(randGenerator) + 1;

	std::uniform_int_distribution<int> varDistribution(PsilLang::varEnums::LASTOUTCOME, PsilLang::varEnums::MYSCORE);

	std::vector<int> lhsVars;
	std::vector<int> rhsVars;

	//First lhs var
	lhsVars.push_back(varDistribution(randGenerator));

	//First rhs var
	rhsVars.push_back(varDistribution(randGenerator));

	int equalityOperator;
	std::vector<int> lhsOperators;
	std::vector<int> rhsOperators;

	//if first variable is LASTOUTCOME it must be compared with w, x, y, z instead of the other variables and operator must be EQUALS
	if (lhsVars[0] == PsilLang::varEnums::LASTOUTCOME)
	{
		equalityOperator = PsilLang::operatorEnums::EQUALS;
		std::uniform_int_distribution<int> wxyzDist(PsilLang::varEnums::W, PsilLang::varEnums::Z);
		//set the other side of the equation to w, x, y or z
		rhsVars[0] = wxyzDist(randGenerator);
		numLhsVars = 1;
		numRhsVars = 1;
	}
	else if (rhsVars[0] == PsilLang::varEnums::LASTOUTCOME)
	{
		equalityOperator = PsilLang::operatorEnums::EQUALS;
		std::uniform_int_distribution<int> wxyzDist(PsilLang::varEnums::W, PsilLang::varEnums::Z);
		lhsVars[0] = wxyzDist(randGenerator);
		numLhsVars = 1;
		numRhsVars = 1;
	}
	//else continue with random variable generation
	else
	{
		//Remove LASTOUTCOME from possible vars
		varDistribution = std::uniform_int_distribution<int>(PsilLang::varEnums::ALLOUTCOMES_W, PsilLang::varEnums::MYSCORE);

		//Populate the rest of the lhs and rhs vars
		for (int i = 1; i < numLhsVars; i++)
		{
			lhsVars.push_back(varDistribution(randGenerator));
		}

		for (int i = 1; i < numRhsVars; i++)
		{
			rhsVars.push_back(varDistribution(randGenerator));
		}

		std::uniform_int_distribution<int> equalityOperatorDistribution(PsilLang::operatorEnums::GREATER_THAN, PsilLang::operatorEnums::EQUALS);

		equalityOperator = equalityOperatorDistribution(randGenerator);

		std::uniform_int_distribution<int> sumOperatorDistribution(PsilLang::operatorEnums::PLUS, PsilLang::operatorEnums::MINUS);

		for (int i = 0; i < numLhsVars - 1; i++)
		{
			lhsOperators.push_back(sumOperatorDistribution(randGenerator));
		}

		for (int i = 0; i < numRhsVars - 1; i++)
		{
			rhsOperators.push_back(sumOperatorDistribution(randGenerator));
		}
	}

	//GOTO line number should be between (current line + 1) and total lines
	//if on 2nd last line go to last line
	int gotoLine = totalLines * 10;		//default to last line
	//if not 2nd last line choose random line greater than current line
	if (currentLineIndex < totalLines - 1)
	{
		std::uniform_int_distribution<int> gotoDistribution(currentLineIndex + 2, totalLines);
		gotoLine = gotoDistribution(randGenerator) * 10;
	}

	std::ostringstream ossLine;
	//Concatenate the final if statement
	//IF
	ossLine << PsilLang::psilKeywords[PsilLang::keywordEnums::IF];

	//Lhs vars and operators
	for (int i = 0; i < numLhsVars; i++)
	{
		ossLine << PsilLang::psilVars[lhsVars[i]];
		if (i < numLhsVars - 1)
		{
			ossLine << PsilLang::psilOperators[lhsOperators[i]];
		}
	}

	//Conditional Operator
	ossLine << PsilLang::psilOperators[equalityOperator];

	//Rhs vars and operators
	for (int i = 0; i < numRhsVars; i++)
	{
		ossLine << PsilLang::psilVars[rhsVars[i]];
		if (i < numRhsVars - 1)
		{
			ossLine << PsilLang::psilOperators[rhsOperators[i]];
		}
	}
	
	ossLine << PsilLang::psilKeywords[PsilLang::keywordEnums::GOTO] << gotoLine;

	std::string lineString = ossLine.str();
	return lineString;
}