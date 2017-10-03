#include <iostream>
#include <string>

using namespace std;

int main()
{
	cout << "Hello" << ' ' << "World" << "\n";
	std::cout << "What is 7 + 2?" << "\n";

	int x;
	int y;

	cout << endl;

	cout << "Enter an int, x: ";
	cin >> x;

	cout << "Enter an int, y: ";
	cin >> y;
	cout << endl;

	char c = 'a';
	bool b = true;
	double d = 12345;

	cout << "x: " << x << endl;
	cout << "y: " << y << endl;

	cout << "Sum of x and y = " << x + y << endl;
	cout << "Product of x and y = " << x * y << "\n\n";

	cout << c << endl;
	cout << b << endl;
	cout << d << endl;

	string name;
	cout << "What is your name? ";
	cin >> name;
	cout << "\nHello " << name << endl;

	cin.ignore();
	cin.get();

	return 0;
}