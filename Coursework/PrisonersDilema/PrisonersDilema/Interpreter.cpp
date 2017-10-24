#include "Interpreter.h"

int Interpreter::interpretDecision(const Prisoner* prisoner)
{
	//Process the first line of the strategy which will recursively process lines until a decision is reached
	int decision = processLine(prisoner, prisoner->getStrategy().begin()->first, 1);
	
	return decision;
}

int Interpreter::processLine(const Prisoner* prisoner, const int lineNumber, const int lineIndex)
{
	//Ensure the strategy file isn't too long
	if (lineIndex > PsilLang::MAX_READ_LINES)
	{
		return Prisoner::decisions::INVALID_FILE;
	}

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

int Interpreter::parseIf(const Prisoner* prisoner, const int lineNumber, const std::vector<std::string>& tokens)
{
	//Initialise next line number to the next line
	//If the if statement returns true this number will be changed to the GOTO number
	std::map<int, std::string>::const_iterator it = prisoner->getStrategy().find(lineNumber);
	it++;
	int nextLineNum = it->first;

	int lhsValue = 0;
	int rhsValue = 0; 

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
	//Sum variables for lhs and rhs
	else
	{
		int tokenIterator = 2;

		if (PsilLang::isInteger(tokens[tokenIterator]))
		{
			lhsValue += std::stoi(tokens[tokenIterator]);
		}
		else
		{
			lhsValue += prisoner->getVariable(PsilLang::stringToEnumMap.at(tokens[tokenIterator]));
		}
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
				if (PsilLang::isInteger(tokens[tokenIterator + 1]))
				{
					lhsValue += std::stoi(tokens[tokenIterator + 1]);
				}
				else
				{
					lhsValue += prisoner->getVariable(PsilLang::stringToEnumMap.at(tokens[tokenIterator + 1]));
				}
			}
			//if MINUS operator
			else
			{
				if (PsilLang::isInteger(tokens[tokenIterator + 1]))
				{
					lhsValue -= std::stoi(tokens[tokenIterator + 1]);
				}
				else
				{
					lhsValue -= prisoner->getVariable(PsilLang::stringToEnumMap.at(tokens[tokenIterator + 1]));
				}
			}
			tokenIterator += 2;
		}

		//Determine the operator in the if statement
		std::string conditionalOperator = tokens[tokenIterator];
		tokenIterator++;

		//rhs var value
		if (PsilLang::isInteger(tokens[tokenIterator]))
		{
			rhsValue += std::stoi(tokens[tokenIterator]);
		}
		else
		{
			rhsValue += prisoner->getVariable(PsilLang::stringToEnumMap.at(tokens[tokenIterator]));
		}
		tokenIterator++;

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
				if (PsilLang::isInteger(tokens[tokenIterator + 1]))
				{
					rhsValue += std::stoi(tokens[tokenIterator + 1]);
				}
				else
				{
					rhsValue += prisoner->getVariable(PsilLang::stringToEnumMap.at(tokens[tokenIterator + 1]));
				}
			}
			//if MINUS operator
			else
			{
				if (PsilLang::isInteger(tokens[tokenIterator + 1]))
				{
					rhsValue -= std::stoi(tokens[tokenIterator + 1]);
				}
				else
				{
					rhsValue -= prisoner->getVariable(PsilLang::stringToEnumMap.at(tokens[tokenIterator + 1]));
				}
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