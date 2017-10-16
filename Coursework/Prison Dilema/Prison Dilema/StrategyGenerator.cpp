#include "StrategyGenerator.h"

void StrategyGenerator::generate(int n)
{
	for (int i = 0; i < n; i++)
	{
		//generate strategy number i
		generateStrategy(i);
	}
}

void StrategyGenerator::generateStrategy(const int index, const int MAX_LINES)
{
	std::ostringstream oss;
	oss << "../Strategies/WriteTest" << index << ".txt";
	std::string filePath = oss.str();

	std::string strategy[MAX_LINES];

	FileManager::writeStringToFile(filePath, strategy[]);
}
