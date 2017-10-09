#include "Player.h"

Player::Player(int hps, string name) :
	hit_points(hps), score(new int(0)), name(new string(name))
{
}

Player::~Player() {
	delete score;
	delete name;
}

int Player::get_hit_points() const {
	return hit_points;
}

int Player::get_score() const {
	return *score;
}

string Player::getName() const
{
	return *name;
}

void Player::set_hit_points(const int new_hit_points) {
	hit_points = new_hit_points;
}

void Player::set_score(const int new_score) {
	*score = new_score;
}

void Player::setName(string newName)
{
	*name = newName;
}

