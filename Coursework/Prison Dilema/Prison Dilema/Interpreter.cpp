#include "Interpreter.h"

int Interpreter::interpretDecision(Prisoner& prisoner)
{
	//Process the first line of the strategy which will recursively process lines until a decision is reached
	int decision = processLine(prisoner, prisoner.getStrategy().begin()->second);
	
	return decision;
}

int Interpreter::processStrategy()
{

	return 0;
}

int Interpreter::processLine(Prisoner& prisoner, const std::string line)
{
	//Copy the first line into a vector of string tokens
	std::istringstream issLine(line);
	std::vector<std::string> tokens;
	std::copy(std::istream_iterator<std::string>(issLine), std::istream_iterator<std::string>(), std::back_inserter(tokens));

	//Check whether first word is line number
	if (!PsilLang::isInteger(tokens[0]))
	{
		std::cout << "Invalid file! No line number found.\n";
		return Prisoner::decisions::INVALID_FILE;
	}

	if (tokens[1] == PsilLang::psilKeywords[PsilLang::keywordEnums::IF])
	{
		parseIf(tokens);
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

		//int random = dist(randomGen);
		//if (random)
		//{
		//	return Prisoner::decisions::BETRAY;
		//}
		//else
		//{
		//	return Prisoner::decisions::SILENCE;
		//}
	}
}

int Interpreter::parseIf(Prisoner& prisoner, const std::vector<std::string>& tokens)
{
	//STRINGTOENUM? MAP???
	//Tokens[even] > 1 is variable
	//Tokens[odd] > 1 is operator

	int tokenIterator = 2;
	int decision = -1;
	int lhsValue = 0;

	int varEnum = PsilLang::stringToEnumMap.at(tokens[2]);

	if (tokens[2] == PsilLang::psilVars[PsilLang::varEnums::LASTOUTCOME])
	{

	}
	else if (tokens[2] == PsilLang::psilVars[PsilLang::varEnums::W] )
	{

	}
	else
	{
		lhsValue += prisoner.getVariable();

		//lhs var
		//loop until equality operator is found
		while (tokens[tokenIterator] != PsilLang::psilOperators[PsilLang::operatorEnums::EQUALS] &&
			tokens[tokenIterator] != PsilLang::psilOperators[PsilLang::operatorEnums::GREATER_THAN] &&
			tokens[tokenIterator] != PsilLang::psilOperators[PsilLang::operatorEnums::LESS_THAN])
		{
			//If even check for var
			if (tokenIterator % 2 == 0)
			{
				//for

				if (tokens[tokenIterator] == PsilLang::psilVars[PsilLang::varEnums::LASTOUTCOME])
				{

				}
			}
			//If odd check for operator
			else
			{

			}

			tokenIterator += 2;
		}
	}

	return decision;
}
