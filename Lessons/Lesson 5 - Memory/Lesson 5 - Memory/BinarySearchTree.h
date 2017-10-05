#pragma once

#include <iostream>
#include <iomanip> 
#include <string>
#include <vector>

using namespace std;

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

	void printPretty(node* tree);
	void printRow(const node* tree, const int height, int depth);
	void getLine(const node* tree, int depth, std::vector<int>& values);
	int getHeight(node* tree);
};

