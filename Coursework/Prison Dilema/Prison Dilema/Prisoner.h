#pragma once

#include <iostream>

#include "FileManager.h"
#include "Globals.h"
#include "Language.h"

class Prisoner
{
public:
	Prisoner(std::string strategyPath);
	~Prisoner();

	void print();

private:
	//static constexpr int MAX_LINES = 20;
	std::string strategyLines[Language::MAXLINES];
};

