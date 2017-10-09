#include <iostream>

using namespace std;

float calc_avg(const int* arr, const int val) {
	int sum = 0;

	for (int i = 0; i < val; ++i)
		sum += arr[i];

	return (sum / (float)val);
}

void initGrid(const int GRID_WIDTH, const int GRID_HEIGHT, char grid[5][5])
{
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			grid[i][j] = '?';
		}
	}
}

void printGrid(const int GRID_WIDTH, const int GRID_HEIGHT, char grid[5][5], bool hideShips = true)
{
	cout << "\n";
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			if (hideShips && grid[i][j] == 'B')
			{
				cout << '?';
			}
			else
			{
				cout << grid[i][j];
			}
		}
		cout << "\n";
	}
	cout << "\n";
}

float calc_avg(const int* arr, const int val);

int main(void) {
	//const int CONST_VALUE = 3;
	//float ave;

	//// stack based 1-d arrays
	//int array_nums[CONST_VALUE] = { 2, 4, 5 };

	//// print out the first element
	//cout << "value at index 0 is " << array_nums[0] << "\n";

	////stack based 2-d arrays
	//char naughts_n_xs[3][3];

	//// set the middle square to x
	//naughts_n_xs[1][1] = 'X';

	////arrays on the heap 1-d
	//int* sum = new int[CONST_VALUE];

	//for (int i = 0; i < CONST_VALUE; ++i)
	//{
	//	cout << "enter a value...\n";
	//	cin >> sum[i];
	//}

	//ave = calc_avg(sum, CONST_VALUE);

	//cout << "the average is " << ave << "\n";

	//cout << "\n";

	const int NAME_LENGTH = 12;
	char name[NAME_LENGTH] = { 'J', 'a', 'c', 'k', ' ' , 'H', 'o', 'o', 'k', 'h', 'a', 'm' };
	for (int i = 0; i < NAME_LENGTH; i++)
	{
		cout << name[i];
	}

	cout << "\n";
	const int FIRST_NAME_LENGTH = 4;
	char* first = new char[FIRST_NAME_LENGTH] { 'J', 'a', 'c', 'k' };

	const int LAST_NAME_LENGTH = 7;
	char* last = new char[LAST_NAME_LENGTH] { 'H', 'o', 'o', 'k', 'h', 'a', 'm' };

	for (int i = 0; i < FIRST_NAME_LENGTH; i++)
	{
		cout << first[i];
	}
	cout << ' ';	
	for (int i = 0; i < LAST_NAME_LENGTH; i++)
	{
		cout << last[i];
	}
	cout << "\n\n\n";

	//delete[] sum;
	delete[] first;
	delete[] last;

	const int GRID_WIDTH = 5;
	const int GRID_HEIGHT = 5;
	char grid[GRID_WIDTH][GRID_HEIGHT];
	//initialise all values to '?'
	initGrid(GRID_WIDTH, GRID_HEIGHT, grid);

	//cout << "\n\n\n";

	//location
	grid[1][0] = 'B';
	grid[2][0] = 'B';
	grid[3][0] = 'B';

	int guesses = 0;
	const int MAX_GUESSES = 5;
	int guess[2];
	bool sunk = false;

	printGrid(GRID_WIDTH, GRID_HEIGHT, grid, true);

	while (!sunk && guesses < MAX_GUESSES)
	{
		cout << "Guesses left: " << MAX_GUESSES - guesses << "\n";
		cout << "Enter x coord: ";
		cin >> guess[0];
		cout << "Enter y coord: ";
		cin >> guess[1];

		guesses++;

		if (grid[guess[1]][guess[0]] == 'B')
		{
			cout << "\nYou sunk my battleship.\n";
			sunk = true;
			grid[guess[1]][guess[0]] = 'H';
			printGrid(GRID_WIDTH, GRID_HEIGHT, grid, false);
		}
		else
		{
			grid[guess[1]][guess[0]] = 'M';
			printGrid(GRID_WIDTH, GRID_HEIGHT, grid, true);
		}
	}

	if (guesses >= MAX_GUESSES)
	{
		cout << "Ran out of guesses.\n";
		printGrid(GRID_WIDTH, GRID_HEIGHT, grid, false);
	}

	//for (int i = 0; i < GRID_WIDTH; i++)
	//{
	//	for (int j = 0; j < GRID_HEIGHT; j++)
	//	{
	//		cout << grid[i][j];
	//	}
	//	cout << "\n";
	//}

	cin.ignore();
	cin.get();

	return 0;
}
