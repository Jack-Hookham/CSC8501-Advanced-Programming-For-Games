#include <iostream>

#include "Enemy.h"
#include "Player.h"
#include "BinarySearchTree.h"

using namespace std;

int main(void) {

	Enemy e1(2);
	cout << "hit points = " << e1.get_hit_points() << "\n";

	Enemy* e2 = new Enemy(2);
	e2->set_hit_points(3);
	cout << "hit points = " << e2->get_hit_points() << "\n";

	e2->set_score(2);
	cout << "score = " << e2->get_score() << "\n";

	delete e2;
	e2 = NULL;

	const int numValues = 10;
	int insertValues[] = { 10, 5, 11, 16, 1, 8, 22, 27, 63, 17 };
	BinarySearchTree* bst = new BinarySearchTree(insertValues, 10);

	bst->printTree(bst->root);
	cout << "\n";

	bst->insertInteger(&bst->root, 12);
	bst->insertInteger(&bst->root, 3);
	bst->insertInteger(&bst->root, 21);

	bst->printTree(bst->root);
	cout << "\n";

	while (true)
	{
		int searchVal;
		cout << "\nEnter integer to search for: ";
		cin >> searchVal;
		if (bst->searchTree(bst->root, searchVal))
		{
			cout << searchVal << " found.";
		}
		else
		{
			cout << searchVal << " not found.";
		}
	}

	delete bst;
	bst = NULL;

	cin.ignore();
	cin.get();

	return 0;
}
