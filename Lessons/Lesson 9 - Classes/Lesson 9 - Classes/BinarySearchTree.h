#pragma once

#include <iostream>
#include <string>

using namespace std;

class BinarySearchTree
{
public:
	BinarySearchTree(int insertValues[], const int NUM_VALUES);
	~BinarySearchTree();

	struct node
	{
		int value;
		struct node* left;
		struct node* right;
	};

	struct node* root = NULL;

	void insertInteger(node** tree, int value);
	void printTree(node* tree);
	void terminateTree(node* tree);
	bool searchTree(node* tree, int value);
};