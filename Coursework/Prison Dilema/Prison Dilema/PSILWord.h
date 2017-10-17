#pragma once

#include <iostream>

class PSILWord
{
public:
	PSILWord();
	~PSILWord();

	inline std::string getName() { return name; }
	inline int getID() { return id; }


private:
	//Prisoner strategy interpretation language
	std::string name;
	int id;
};

