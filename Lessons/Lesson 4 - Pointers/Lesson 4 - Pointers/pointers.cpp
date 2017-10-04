#include <iostream>

using namespace std;

void mySwap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void printEven(int arr[])
{
	cout << endl;
	int* ptr = arr;
	ptr++;
	for (; *ptr <= 10; ptr+=2)
	{
		cout << *ptr << endl;
	}
}

int main() {

	int a = 100;

	cout << "Value in memory location a is " << a << "\n";

	cout << "Address of (the reference to) memory location a is " << &a << "\n";

	int *b = &a;

	cout << "Value in memory location pointed to by b is " << *b << "\n";


	cout << "Value in memory location b is " << b << "\n";
	cout << b << " should be the same as the memory location for a: " << &a << "\n";
	cout << "b is actually at memory location " << &b << endl;

	int** c;

	c = &b;
	cout << "c is now pointing to what b points to: " << **c << endl;

	cout << "c points to: " << *c << endl;

	cout << "c actually holds the value: " << c << endl;
	cout << c << " is the same value as b's memory location: " << &b << endl;
	cout << "c is actually at memory location " << &c << endl;

	cout << "c is eventually retrieving what is in memory location " << **&c << endl;
	cout << "the value of a is in memory location " << &a << endl;

	int x = 10;
	int y = 15;
	int* px = &x;
	int* py = &y;

	cout << "\npx = " << *px << "\npy = " << *py << endl;
	mySwap(px, py);
	cout << "px = " << *px << "\npy = " << *py << endl;

	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	printEven(arr);

	cin.ignore();
	cin.get();

	return 0;
}
