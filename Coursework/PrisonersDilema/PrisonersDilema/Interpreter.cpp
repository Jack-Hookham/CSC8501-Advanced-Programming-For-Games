#include "Interpreter.h"

int Interpreter::interpretDecision(Prisoner* prisoner)
{
	//Process the first line of the strategy which will recursively process lines until a decision is reached
	int decision = processLine(prisoner, prisoner->getStrategy().begin()->first);
	
	return decision;
}

int Interpreter::processLine(Prisoner* prisoner, const int lineNumber)
{
	//Copy the first line into a vector of string tokens
	std::istringstream issLine(prisoner->getStrategyLine(lineNumber));
	std::vector<std::string> tokens;
	std::copy(std::istream_iterator<std::string>(issLine), std::istream_iterator<std::string>(), std::back_inserter(tokens));

	//Check whether first word is an integer
	if (!PsilLang::isInteger(tokens[0]))
	{
		//error
		std::cout << "Invalid file! No line number found.\n";
		return Prisoner::decisions::INVALID_FILE;
	}
	if (tokens[1] == PsilLang::psilKeywords[PsilLang::keywordEnums::IF])
	{
		//Parse the if statement which will then call processLine again on the resulting line number
		return parseIf(prisoner, lineNumber, tokens);
		//processLine(prisoner, nextLineNumber);
	}
	else if (tokens[1] == PsilLang::psilKeywords[PsilLang::keywordEnums::BETRAY])
	{
		return Prisoner::decisions::BETRAY;
	}
	else if (tokens[1] == PsilLang::psilKeywords[PsilLang::keywordEnums::SILENCE])
	{
		return Prisoner::decisions::SILENCE;
	}
	else if (tokens[1] == PsilLang::psilKeywords[PsilLang::keywordEnums::RANDOM])
	{
		//Choose BETRAY(0) or SILENCE(1)
		std::random_device rd;
		std::mt19937 randomGen(rd());
		std::uniform_int_distribution<int> dist(0, 1);
		return dist(randomGen);
	}
	else
	{
		//error
		std::cout << "Invalid file! Invalid word found.\n";
		return Prisoner::decisions::INVALID_FILE;
	}
}

int Interpreter::parseIf(Prisoner* prisoner, const int lineNumber, const std::vector<std::string>& tokens)
{
	////STRINGTOENUM? MAP???
	////Tokens[even] > 1 is variable
	////Tokens[odd] > 1 is operator

	//Initialise next line number to the next line
	//If the if statement returns true this number will be changed to the GOTO number
	std::map<int, std::string>::const_iterator it = prisoner->getStrategy().find(lineNumber);
	it++;
	int nextLineNum = it->first;

	int lhsEnum = PsilLang::stringToEnumMap.at(tokens[2]);

	//lhs = LASTOUTCOME
	if (tokens[2] == PsilLang::psilVars[PsilLang::varEnums::LASTOUTCOME])
	{
		if (tokens[3] == PsilLang::psilOperators[PsilLang::operatorEnums::EQUALS])
		{
			if (prisoner->getVariable(PsilLang::LASTOUTCOME) == PsilLang::stringToEnumMap.at(tokens[4]))
			{
				if (PsilLang::isInteger(tokens[6]))
				{
					nextLineNum = std::stoi(tokens[6]);
				}
				else
				{
					//error expected int line number
					std::cout << "Invalid strategy file, expected int line number\n";
				}
			}
			//switch (PsilLang::stringToEnumMap.at(tokens[4]))
			//{
			//case PsilLang::varEnums::W:
			//	if (prisoner->getVariable(PsilLang::LASTOUTCOME) == PsilLang::varEnums::W)
			//	{
			//		conditionalResult = true;
			//	}
			//case PsilLang::varEnums::X:
			//	if (prisoner->getVariable(PsilLang::LASTOUTCOME) == PsilLang::varEnums::X)
			//	{
			//		conditionalResult = true;
			//	}
			//case PsilLang::varEnums::Y:
			//	if (prisoner->getVariable(PsilLang::LASTOUTCOME) == PsilLang::varEnums::Y)
			//	{
			//		conditionalResult = true;
			//	}
			//case PsilLang::varEnums::Z:
			//	if (prisoner->getVariable(PsilLang::LASTOUTCOME) == PsilLang::varEnums::Z)
			//	{
			//		conditionalResult = true;
			//	}
			//default:
			//	//error
			//	std::cout << "rhs was invalid";
			//	return Prisoner::decisions::INVALID_FILE;
			//}
		}
		else
		{
			//error operator should be equals
			std::cout << "Invalid strategy. = operator expected\n";
		}
	}
	//rhs = LASTOUTCOME
	else if (tokens[4] == PsilLang::psilVars[PsilLang::varEnums::LASTOUTCOME])
	{
		if (tokens[3] == PsilLang::psilOperators[PsilLang::operatorEnums::EQUALS])
		{
			if (prisoner->getVariable(PsilLang::LASTOUTCOME) == PsilLang::stringToEnumMap.at(tokens[2]))
			{			
				if (PsilLang::isInteger(tokens[6]))
				{
					nextLineNum = std::stoi(tokens[6]);
				}
				else
				{
					//error expected int line number
					std::cout << "Invalid strategy file, expected int line number\n";
				}
			}
		}
		else
		{
			//error operator should be equals
			std::cout << "Invalid strategy. EQUALS operator expected\n";
		}
	}
	//Sum variables
	else
	{
		int tokenIterator = 2;
		int lhsValue = prisoner->getVariable(PsilLang::stringToEnumMap.at(tokens[tokenIterator]));
		tokenIterator++;
		//lhs var value
		//loop until equality operator is found
		while (tokens[tokenIterator] != PsilLang::psilOperators[PsilLang::operatorEnums::EQUALS] &&
			tokens[tokenIterator] != PsilLang::psilOperators[PsilLang::operatorEnums::GREATER_THAN] &&
			tokens[tokenIterator] != PsilLang::psilOperators[PsilLang::operatorEnums::LESS_THAN])
		{
			if (tokens[tokenIterator + 1] == PsilLang::psilVars[PsilLang::varEnums::LASTOUTCOME])
			{
				//error
				std::cout << "Invalid strategy. LASTOUTCOME invalid here.\n";
			}
			//if PLUS operator
			if (tokens[tokenIterator] == PsilLang::psilOperators[PsilLang::operatorEnums::PLUS])
			{
				lhsValue += prisoner->getVariable(PsilLang::stringToEnumMap.at(tokens[tokenIterator + 1]));
			}
			//if MINUS operator
			else
			{
				lhsValue -= prisoner->getVariable(PsilLang::stringToEnumMap.at(tokens[tokenIterator + 1]));
			}
			tokenIterator += 2;
		}

		//Determine the operator in the if statement
		std::string conditionalOperator = tokens[tokenIterator];
		tokenIterator++;
		int rhsValue = prisoner->getVariable(PsilLang::stringToEnumMap.at(tokens[tokenIterator]));
		tokenIterator++;
		//rhs var value
		//loop until GOTO keyword is found
		while (tokens[tokenIterator] != PsilLang::psilKeywords[PsilLang::keywordEnums::GOTO])
		{
			if (tokens[tokenIterator + 1] == PsilLang::psilVars[PsilLang::varEnums::LASTOUTCOME])
			{
				//error
				std::cout << "Invalid strategy. LASTOUTCOME invalid here.\n";
			}
			//if PLUS operator
			if (tokens[tokenIterator] == PsilLang::psilOperators[PsilLang::operatorEnums::PLUS])
			{
				rhsValue += prisoner->getVariable(PsilLang::stringToEnumMap.at(tokens[tokenIterator + 1]));
			}
			//if MINUS operator
			else
			{
				rhsValue -= prisoner->getVariable(PsilLang::stringToEnumMap.at(tokens[tokenIterator + 1]));
			}
			tokenIterator += 2;
		}

		if ((conditionalOperator == PsilLang::psilOperators[PsilLang::operatorEnums::GREATER_THAN] && lhsValue > rhsValue) ||
			(conditionalOperator == PsilLang::psilOperators[PsilLang::operatorEnums::LESS_THAN] && lhsValue < rhsValue) ||
			(conditionalOperator == PsilLang::psilOperators[PsilLang::operatorEnums::EQUALS] && lhsValue == rhsValue))
		{
			tokenIterator++;
			if (PsilLang::isInteger(tokens[tokenIterator]))
			{
				nextLineNum = std::stoi(tokens[tokenIterator]);
			}
			else
			{
				//error expected int line number
				std::cout << "Invalid strategy file, expected int line number\n";
			}
		}
	}

	return processLine(prisoner, nextLineNum);
}

//functions
//equalsCheck()
//<check()
//>check()
//check for goto