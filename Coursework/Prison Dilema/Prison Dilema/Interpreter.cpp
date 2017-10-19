#include "Interpreter.h"

int Interpreter::interpretDecision(Prisoner& prisoner)
{
	int decision = Prisoner::decisions::INVALID_FILE;

	//Copy the first line into a vector of strings
	std::string currentLine = prisoner.getStrategyLine(0);
	std::istringstream issLine(currentLine);
	std::vector<std::string> tokens;
	std::copy(std::istream_iterator<std::string>(issLine), std::istream_iterator<std::string>(), std::back_inserter(tokens));

	//Check whether first word is line number
	if (!Language::isInteger(tokens[0]))
	{
		std::cout << "Invalid file! No line number found.\n";
		return decision;
	}
	else
	{
		if (tokens[1] == "IF")
		{
			//(keywordIf())
		}
	}

	//int currentLineNumber = tokens[0];

	//while (decision == Prisoner::decisions::INVALID_FILE)
	{
	}
	

	return decision;
}

int Interpreter::compareStrategies(Prisoner& prisonerA, Prisoner& prisonerB)
{
	int result;

	

	return result = 0;
}
