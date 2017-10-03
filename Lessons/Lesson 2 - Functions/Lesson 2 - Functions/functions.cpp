#include <iostream>

using namespace std;

inline int add(int x, int y) { return x + y; }
inline int subtract(int x, int y);
inline void product(int x, int y) { cout << x << " * " << y << " = " << x * y << "\n"; }
inline double quotient(double x, double y) { return x / y; }

int main()
{
	int a, b, c;

	cout << "Please type in a number: ";
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
