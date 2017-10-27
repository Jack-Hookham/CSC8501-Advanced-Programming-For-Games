#include "Interpreter.h"

int Interpreter::interpretDecision(const Prisoner* prisoner)
{
	double timeTaken = 0;
	//Process the first line of the strategy which will recursively process lines until a decision is reached
	int decision = processLine(timeTaken, prisoner, prisoner->getStrategy().begin()->first, 1);
	
	return decision;
}

int Interpreter::processLine(double timeTaken, const Prisoner* prisoner, const int lineNumber, const int lineIndex)
{
	double startTime = GetTickCount();
	if (timeTaken > 30)
	{
		//Ensure no infinite loop
		std::cout << "Invalid file: Interpreter took too long.\n";
		return Prisoner::decisions::INVALID_FILE;
	}
	//Ensure the strategy file isn't too long
	if (lineIndex > PsiLang::MAX_READ_LINES)
	{
		return Prisoner::decisions::INVALID_FILE;
	}

	//Copy the first line into a vector of string tokens
	std::istringstream issLine(prisoner->getStrategyLine(lineNumber));
	std::vector<std::string> tokens;
	std::copy(std::istream_iterator<std::string>(issLine), std::istream_iterator<std::string>(), std::back_inserter(tokens));

	//Check whether first word is an integer
	if (!PsiLang::isInteger(tokens[0]))
	{
		//error
		std::cout << "Invalid file! No line number found.\n";
		return Prisoner::decisions::INVALID_FILE;
	}
	if (tokens[1] == PsiLang::psilKeywords[PsiLang::keywordEnums::IF])
	{
		timeTaken += GetTickCount() - startTime;
		//Parse the if statement which will then call processLine again on the resulting line number
		return parseIf(timeTaken, prisoner, lineNumber, tokens);
		//processLine(prisoner, nextLineNumber);
	}
	else if (tokens[1] == PsiLang::psilKeywords[PsiLang::keywordEnums::BETRAY])
	{
		return Prisoner::decisions::BETRAY;
	}
	else if (tokens[1] == PsiLang::psilKeywords[PsiLang::keywordEnums::SILENCE])
	{
		return Prisoner::decisions::SILENCE;
	}
	else if (tokens[1] == PsiLang::psilKeywords[PsiLang::keywordEnums::RANDOM])
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

int Interpreter::parseIf(double timeTaken, const Prisoner* prisoner, const int lineNumber, const std::vector<std::string>& tokens)
{
	double startTime = GetTickCount();
	//Ensure no infinite loop
	if (timeTaken > 30)
	{
		std::cout << "Invalid file: Interpreter took too long.\n";
		return Prisoner::decisions::INVALID_FILE;
	}
	//Initialise next line number to the next line
	//If the if statement returns true this number will be changed to the GOTO number
	std::map<int, std::string>::const_iterator it = prisoner->getStrategy().find(lineNumber);
	it++;
	int nextLineNum = it->first;

	int lhsValue = 0;
	int rhsValue = 0; 

	//lhs = LASTOUTCOME
	if (tokens[2] == PsiLang::psilVars[PsiLang::varEnums::LASTOUTCOME])
	{
		if (tokens[3] == PsiLang::psilOperators[PsiLang::operatorEnums::EQUALS])
		{
			if (prisoner->getVariable(PsiLang::LASTOUTCOME) == PsiLang::stringToEnumMap.at(tokens[4]))
			{
				if (PsiLang::isInteger(tokens[6]))
				{
					nextLineNum = std::stoi(tokens[6]);
				}
				else
				{
					//error expected int line number
					std::cout << "Invalid strategy file, expected int line number\n";
					return Prisoner::decisions::INVALID_FILE;
				}
			}
		}
		else
		{
			//error operator should be equals
			std::cout << "Invalid strategy. = operator expected\n";
			return Prisoner::decisions::INVALID_FILE;
		}
	}
	//rhs = LASTOUTCOME
	else if (tokens[4] == PsiLang::psilVars[PsiLang::varEnums::LASTOUTCOME])
	{
		if (tokens[3] == PsiLang::psilOperators[PsiLang::operatorEnums::EQUALS])
		{
			if (prisoner->getVariable(PsiLang::LASTOUTCOME) == PsiLang::stringToEnumMap.at(tokens[2]))
			{			
				if (PsiLang::isInteger(tokens[6]))
				{
					nextLineNum = std::stoi(tokens[6]);
				}
				else
				{
					//error expected int line number
					std::cout << "Invalid strategy file, expected int line number\n";
					return Prisoner::decisions::INVALID_FILE;
				}
			}
		}
		else
		{
			//error operator should be equals
			std::cout << "Invalid strategy. EQUALS operator expected\n";
			return Prisoner::decisions::INVALID_FILE;
		}
	}
	//Sum variables for lhs and rhs
	else
	{
		int tokenIterator = 2;

		if (PsiLang::isInteger(tokens[tokenIterator]))
		{
			lhsValue += std::stoi(tokens[tokenIterator]);
		}
		else
		{
			lhsValue += prisoner->getVariable(PsiLang::stringToEnumMap.at(tokens[tokenIterator]));
		}
		tokenIterator++;
		//lhs var value
		//loop until equality operator is found
		while (tokens[tokenIterator] != PsiLang::psilOperators[PsiLang::operatorEnums::EQUALS] &&
			tokens[tokenIterator] != PsiLang::psilOperators[PsiLang::operatorEnums::GREATER_THAN] &&
			tokens[tokenIterator] != PsiLang::psilOperators[PsiLang::operatorEnums::LESS_THAN])
		{
			if (tokens[tokenIterator + 1] == PsiLang::psilVars[PsiLang::varEnums::LASTOUTCOME])
			{
				//error
				std::cout << "Invalid strategy. LASTOUTCOME invalid here.\n";
				return Prisoner::decisions::INVALID_FILE;
			}
			//if PLUS operator
			if (tokens[tokenIterator] == PsiLang::psilOperators[PsiLang::operatorEnums::PLUS])
			{
				if (PsiLang::isInteger(tokens[tokenIterator + 1]))
				{
					lhsValue += std::stoi(tokens[tokenIterator + 1]);
				}
				else
				{
					lhsValue += prisoner->getVariable(PsiLang::stringToEnumMap.at(tokens[tokenIterator + 1]));
				}
			}
			//if MINUS operator
			else
			{
				if (PsiLang::isInteger(tokens[tokenIterator + 1]))
				{
					lhsValue -= std::stoi(tokens[tokenIterator + 1]);
				}
				else
				{
					lhsValue -= prisoner->getVariable(PsiLang::stringToEnumMap.at(tokens[tokenIterator + 1]));
				}
			}
			tokenIterator += 2;
		}

		//Determine the operator in the if statement
		std::string conditionalOperator = tokens[tokenIterator];
		tokenIterator++;

		//rhs var value
		if (PsiLang::isInteger(tokens[tokenIterator]))
		{
			rhsValue += std::stoi(tokens[tokenIterator]);
		}
		else
		{
			rhsValue += prisoner->getVariable(PsiLang::stringToEnumMap.at(tokens[tokenIterator]));
		}
		tokenIterator++;

		//loop until GOTO keyword is found
		while (tokens[tokenIterator] != PsiLang::psilKeywords[PsiLang::keywordEnums::GOTO])
		{
			if (tokens[tokenIterator + 1] == PsiLang::psilVars[PsiLang::varEnums::LASTOUTCOME])
			{
				//error
				std::cout << "Invalid strategy. LASTOUTCOME invalid here.\n";
				return Prisoner::decisions::INVALID_FILE;
			}
			//if PLUS operator
			if (tokens[tokenIterator] == PsiLang::psilOperators[PsiLang::operatorEnums::PLUS])
			{
				if (PsiLang::isInteger(tokens[tokenIterator + 1]))
				{
					rhsValue += std::stoi(tokens[tokenIterator + 1]);
				}
				else
				{
					rhsValue += prisoner->getVariable(PsiLang::stringToEnumMap.at(tokens[tokenIterator + 1]));
				}
			}
			//if MINUS operator
			else
			{
				if (PsiLang::isInteger(tokens[tokenIterator + 1]))
				{
					rhsValue -= std::stoi(tokens[tokenIterator + 1]);
				}
				else
				{
					rhsValue -= prisoner->getVariable(PsiLang::stringToEnumMap.at(tokens[tokenIterator + 1]));
				}
			}
			tokenIterator += 2;
		}

		if ((conditionalOperator == PsiLang::psilOperators[PsiLang::operatorEnums::GREATER_THAN] && lhsValue > rhsValue) ||
			(conditionalOperator == PsiLang::psilOperators[PsiLang::operatorEnums::LESS_THAN] && lhsValue < rhsValue) ||
			(conditionalOperator == PsiLang::psilOperators[PsiLang::operatorEnums::EQUALS] && lhsValue == rhsValue))
		{
			tokenIterator++;
			if (PsiLang::isInteger(tokens[tokenIterator]))
			{
				nextLineNum = std::stoi(tokens[tokenIterator]);
			}
			else
			{
				//error expected int line number
				std::cout << "Invalid strategy file, expected int line number\n";
				return Prisoner::decisions::INVALID_FILE;
			}
		}
	}

	timeTaken += GetTickCount() - startTime;
	return processLine(timeTaken, prisoner, nextLineNum);
}