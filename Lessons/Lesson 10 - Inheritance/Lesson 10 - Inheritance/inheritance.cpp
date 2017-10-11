#include <iostream>

using namespace std;

// declare enemy class

class Enemy {
public:
	Enemy(int hps);
	virtual ~Enemy();
	virtual int get_hit_points() const;
	virtual int get_score() const;
	virtual void set_hit_points(int new_hit_points);
	virtual	void set_score(int new_score);
protected:
	int hit_points;
	int* score;
};

// define enemy class

Enemy::Enemy(int hps) :
	hit_points(hps) {
	score = new int(0);
}

Enemy::~Enemy() {
	delete score;
}

int Enemy::get_hit_points() const {
	return hit_points;
}

int Enemy::get_score() const {
	return *score;
}

void Enemy::set_hit_points(const int new_hit_points) {
	hit_points = new_hit_points;
}

void Enemy::set_score(const int new_score) {
	*score = new_score;
}

// declare flying enemy class

class ArmedEnemy : public Enemy
{
public:
	ArmedEnemy(int hps, int ammo);
	virtual ~ArmedEnemy();
	virtual void set_score(const int new_score);
	virtual void shoot();
protected:
	int ammo_level;
};

// define flying enemy class

ArmedEnemy::ArmedEnemy(int hps, int ammo) :
	Enemy(hps),
	ammo_level(ammo) {
}

ArmedEnemy::~ArmedEnemy() {
}

void ArmedEnemy::set_score(const int new_score) {
	*score = new_score;
	cout << "score is now " << *score << "\n";
}

void ArmedEnemy::shoot() {
	if (ammo_level > 0)
	{
		cout << "bang!\n";
		--ammo_level;
	}
	else
	{
		cout << "out of ammo\n";
	}
}

class Boss : public ArmedEnemy
{
public :
	Boss(int hps, int ammo, int armour);
	virtual ~Boss();
	
	virtual void setArmour(int armour);
	virtual int getArmour();
protected:
	int armourLevel;
};

Boss::Boss(int hps, int ammo, int armour) :
	ArmedEnemy(hps, ammo),
	armourLevel(armour)
{
}

Boss::~Boss()
{
}

void Boss::setArmour(int armour)
{
	armourLevel = armour;
}

int Boss::getArmour()
{
	return armourLevel;
}

void some_function(Enemy& enemy) {
	enemy.set_score(6);
}

void decrementHP(Enemy& enemy)
{
	enemy.set_hit_points(enemy.get_hit_points() - 1);
}

int main(void) {

	//ArmedEnemy* ae = new ArmedEnemy(2, 5);
	//ae->set_hit_points(3);
	//cout << "hit points = " << ae->get_hit_points() << "\n";

	//ae->shoot();

	//some_function(*ae);

	const int numArmedEnemies = 10;
	ArmedEnemy* armedEnemies[numArmedEnemies];
	for (int i = 0; i < numArmedEnemies; i++)
	{
		armedEnemies[i] = new ArmedEnemy(2, 5);
	}

	Boss* boss = new Boss(3, 6, 3);

	const int numAllEnemies = 11;
	Enemy* allEnemies[numAllEnemies];
	allEnemies[0] = boss;
	for (int i = 0; i < numArmedEnemies; i++)
	{
		allEnemies[i + 1] = armedEnemies[i];
	}

	for (int i = 0; i < numAllEnemies; i++)
	{
		cout << "HP " << i << ':' << allEnemies[i]->get_hit_points() << "\n";
	}
	cout << "\n";

	for (int i = 0; i < numAllEnemies; i++)
	{
		decrementHP(*allEnemies[i]);
	}

	for (int i = 0; i < numAllEnemies; i++)
	{
		cout << "HP " << i << ':' << allEnemies[i]->get_hit_points() << "\n";
	}

	//delete ae;
	//ae = NULL;
	for (int i = 0; i < numAllEnemies; i++)
	{
		delete allEnemies[i];
		allEnemies[i] = NULL;
	}
	cin.ignore();
	cin.get();

	return 0;
}
