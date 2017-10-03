#include <iostream>

using namespace std;

inline int add(int x, int y) { return x + y; }
inline int subtract(int x, int y);
//inline void product(int x, int y) { cout << x << " * " << y << " = " << x * y << "\n"; }
inline int product(int x, int y) { return x * y; }
inline double quotient(double x, double y) { return x / y; }

void calculator()
{
	int x, y;
	double z;
	char op;

	cout << "Enter an integer, x: ";
	cin >> x;
	while (cin.fail())
	{
		cout << "Not an integer\n";
		cout << "Enter an integer, x: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> x;
	} 

	cout << "Enter an integer, y: ";
	cin >> y;
	while (cin.fail())
	{
		cout << "Not an integer\n";
		cout << "Enter an integer, y: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> y;
	}

	bool validOp = false;

	while (!validOp)
	{
		cout << "Enter an operator +, -, * or / : ";		
		cin >> op;

		switch (op)
		{
		case 43: //+
			z = add(x, y);
			cout << x << " + " << y << " = " << z << "\n";
			validOp = true;
			break;
		case 45: //-
			z = subtract(x, y);
			cout << x << " - " << y << " = " << z << "\n";
			validOp = true;
			break;
		case 42: //*
			z = product(x, y);
			cout << x << " * " << y << " = " << z << "\n";
			validOp = true;
			break;
		case 47: // /
			z = quotient((double)x, (double)y);
			cout << x << " / " << y << " = " << z << "\n";
			validOp = true;
			break;
		default:
			cout << "Not a valid operator!\n";
			break;
		}
	}

	cin.ignore();
	cin.get();
}

int main()
{
	calculator();

	int a, b, c;

	cout << "\nPlease type in a number: ";
	cin >> a;
	cout << "\nPlease type in another number: ";
	cin >> b;

	c = add(a, b);

	cout << a << " + " << b << " = " << c << "\n";
	cout << a << " - " << b << " = " << subtract(a, b) << "\n";
	product(a, b);
	cout << a << " / " << b << " = " << quotient((double)a, (double)b) << "\n";

	cin.ignore();
	cin.get();

	return 0;
}

inline int subtract(int x, int y) { return x - y; }
