#pragma once

#include <iostream>
#include <vector>

#include "FileManager.h"
#include "Globals.h"
#include "Language.h"

class Prisoner
{
public:
	//Prisoner constructor reads a strategy from file and adds each line to the strategy array
	Prisoner(std::string filePath);
	~Prisoner();

	void print();

private:
	std::vector<std::string> strategy;
};

