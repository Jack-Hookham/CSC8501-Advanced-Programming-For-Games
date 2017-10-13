#pragma once

#include <iostream>

#include "FileManager.h"

using namespace std;

class Prisoner
{
public:
	Prisoner(string strategyPath);
	~Prisoner();

	void print();

private:
	static constexpr int MAX_LINES = 20;
	string strategyLines[MAX_LINES];
};

