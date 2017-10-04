#include <iostream>

using namespace std;

bool greaterThanZero(int x)
{
	return x > 0;
}

void loopWhilePositive()
{
	int x;
	cout << "Enter an integer: ";
	cin >> x;
	while (greaterThanZero(x))
	{
		cout << "Enter an integer: ";
		cin >> x;
	}
	cout << "NEGATIVE!\n";
}

int add(int x, int y) 
{
	return x + y;
}

int fac(int x) 
{

	int facSum = 1;

	for (int count = x; count > 0; count--)
		facSum = facSum * count;

	return facSum;
}

int main() 
{
	loopWhilePositive();

	int x;

	cout << "\nEnter an integer, x: ";
	cin >> x;
	cout << "x > 0: " << greaterThanZero(x) << endl;

	int total = 0;

	cout << "\nPlease enter numbers, will finish if sum of factorals exceeds 2000" << "\n";

	while (total <= 2000) 
	{
		cin >> x;
		total = add(fac(x), total);
	}

	cout << "The total is " << total << "\n";

	if (total > 3000)
		cout << "you overshot by a lot!" << "\n";
	else 
	{
		cout << "You just went over" << "\n";
		cout << "Only over by " << total - 2000 << "\n";
	}

	cin.get();
	cin.ignore();

	return 0;
}
