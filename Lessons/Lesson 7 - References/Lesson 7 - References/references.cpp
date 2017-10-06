#include <iostream>

using namespace std;

void swap(int x, int y) {
	int temp = x;
	x = y;
	y = temp;
}

void swap(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void swap_ref(int& x, int& y) {
	int temp = x;
	x = y;
	y = temp;
}

int main() {
	int x = 3, y = 4;	int& x_ref = x;	cout << x_ref << "\n";	x_ref = y;	cout << x_ref << "\n";

	int a, b;

	cout << "Please type in a number" << "\n";
	cin >> a;
	cout << "Please type in another number" << "\n";
	cin >> b;

	cout << "before swap, a = " << a << " and b = " << b << "\n";
	swap(a, b);
	cout << "after swap (by value), a = " << a << " and b = " << b << "\n";
	swap(&a, &b);
	cout << "after swap by pointer reference, a = " << a << " and b = " << b << "\n";

	swap_ref(a, b);
	cout << "after swap using references, a = " << a << " and b = " << b << "\n";

	int& a_ref = a;
	return 0;
}
