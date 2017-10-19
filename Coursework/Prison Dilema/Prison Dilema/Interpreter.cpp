#include "Interpreter.h"

int Interpreter::interpretDecision(Prisoner& prisoner)
{
	//Process the first line of the strategy
	int decision = processLine(prisoner.getStrategy().begin()->second);

	

	//int currentLineNumber = tokens[0];

	//while (decision == Prisoner::decisions::INVALID_FILE)
	{
	}
	
	return decision;
}

int Interpreter::processStrategy()
{

	return 0;
}

int Interpreter::processLine(const std::string line)
{
	//Copy the first line into a vector of string tokens
	std::istringstream issLine(line);
	std::vector<std::string> tokens;
	std::copy(std::istream_iterator<std::string>(issLine), std::istream_iterator<std::string>(), std::back_inserter(tokens));

	//Check whether first word is line number
	if (!Language::isInteger(tokens[0]))
	{
		std::cout << "Invalid file! No line number found.\n";
		return Prisoner::decisions::INVALID_FILE;
	}

	if (tokens[1] == "IF")
	{
		parseIf(tokens);
	}
	else if (tokens[1] == "BETRAY")
	{
		return Prisoner::decisions::BETRAY;
	}
	else if (tokens[1] == "SILENCT")
	{
		return Prisoner::decisions::SILENT;
	}
	else if (tokens[1] == "RANDOM")
	{
		std::random_device rd;
		std::mt19937 randomGen(rd());
		std::uniform_int_distribution<int> dist(0, 1);
		int random = dist(randomGen);
		if (random)
		{
			return Prisoner::decisions::BETRAY;
		}
		else
		{
			return Prisoner::decisions::SILENT;
		}
	}
}

int Interpreter::parseIf(const std::vector<std::string>& tokens)
{

}
