#include "NonRecursiveBST.h"

NonRecursiveBST::NonRecursiveBST(int insertValues[], const int NUM_VALUES)
{
}

NonRecursiveBST::~NonRecursiveBST()
{
	terminateTree(root);
}

void NonRecursiveBST::insertInteger(struct node** tree, int value)
{
	//store the current node and its parent
	node* currentNode = *tree;
	node* parentNode = NULL;

	//if the tree is empty give it the value
	if (*tree == NULL)
	{
		*tree = new node;
		(*tree)->value = value;

		//initialise the left and right branches of the node to NULL
		(*tree)->left = NULL;
		(*tree)->right = NULL;
	}

	//while no empty node is found
	while (currentNode != NULL)
	{
		//if value < current branch value go left
		if (value < currentNode->value)
		{
			//update parent and current node values
			parentNode = currentNode;
			currentNode = currentNode->left;
			cout << "Go left";
		}
		//value <= current branch value go right
		else
		{
			parentNode = currentNode;
			currentNode = currentNode->right;
			cout << "Go right";
		}
	}
	//Once an empty node is found we can populate that node
	//Create the node
	node* newNode = new node;
	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;

	//Insert the node
	if (value < parentNode->value)
	{
		parentNode->left->value = value;
	}
	else
	{
		parentNode->right->value = value;
	}
}

void NonRecursiveBST::printTree(node* tree)
{
	if (tree == NULL)
	{
		return;
	}

	printTree(tree->left);
	cout << tree->value << ' ';
	printTree(tree->right);
}

void NonRecursiveBST::terminateTree(node* tree)
{
	if (tree != NULL)
	{
		terminateTree(tree->left);
		terminateTree(tree->right);
		delete tree;
	}
}

bool NonRecursiveBST::searchTree(node* tree, int value)
{
	if (tree != NULL)
	{
		if (value == tree->value)
		{
			return true;
		}
		else if (value < tree->value)
		{
			searchTree(tree->left, value);
		}
		else if (value > tree->value)
		{
			searchTree(tree->right, value);
		}
	}
	else
	{
		return false;
	}
}

