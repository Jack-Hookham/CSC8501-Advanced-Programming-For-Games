#pragma once

#include <iostream>
#include <string>

class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();

	struct node
	{
		int value;
		struct node* left;
		struct node* right;
	};

	int depth = 0;
	struct node* root = NULL;

	void insertInteger(struct node** tree, int value);
	void printTree(struct node* tree);
	void terminateTree(struct node* tree);
};

