#include "Interpreter.h"

int Interpreter::interpretDecision(Prisoner& prisoner)
{
	int decision = Prisoner::decisions::INVALID_FILE;
	//Check whether first word is line number

	std::string currentLine = prisoner.getStrategyLine(0);
	std::istringstream issLine(currentLine);
	std::vector<std::string> tokens;
	std::copy(std::istream_iterator<std::string>(issLine), std::istream_iterator<std::string>(), std::back_inserter(tokens));

	for (int i = 0; i < tokens.size(); i++)
	{
		std::cout << tokens[i] + ' ';
	}

	while (decision == Prisoner::decisions::INVALID_FILE)
	{
	}
	

	return decision;
}

int Interpreter::compareStrategies(Prisoner& prisonerA, Prisoner& prisonerB)
{
	int result;

	

	return result = 0;
}
