#pragma once
#include <iostream>

using namespace std;

class Player
{
public:
	Player(int hps, string name);
	~Player();
	int get_hit_points() const;
	int get_score() const;
	string getName() const;
	void set_hit_points(int new_hit_points);
	void set_score(int new_score);
	void setName(string newName);
private:
	int hit_points;
	int* score;
	string* name;
};