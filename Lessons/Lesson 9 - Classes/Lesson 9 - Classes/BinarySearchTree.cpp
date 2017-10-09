#include "BinarySearchTree.h"


BinarySearchTree::BinarySearchTree(int insertValues[] = {}, const int NUM_VALUES = 0)
{
	for (int i = 0; i < NUM_VALUES; i++)
	{
		insertInteger(&root, insertValues[i]);
	}
}

BinarySearchTree::~BinarySearchTree()
{
	terminateTree(root);
}

void BinarySearchTree::insertInteger(node** tree, int value)
{
	//if the tree is empty give it the value
	if (*tree == NULL)
	{
		*tree = new node;
		(*tree)->value = value;

		//initialise the left and right branches of the node to NULL
		(*tree)->left = NULL;
		(*tree)->right = NULL;
	}
	else
	{
		//if value is < root go left
		if (value < (*tree)->value)
		{
			//if left has a value go deeper into the tree recursively
			if ((*tree)->left != NULL)
			{
				insertInteger(&(*tree)->left, value);
			}
			//else set left to value
			else
			{
				(*tree)->left = new node;
				(*tree)->left->value = value;

				//initialise the left and right branches of the node to NULL
				(*tree)->left->left = NULL;
				(*tree)->left->right = NULL;
			}
		}
		//value is >= root go right
		else
		{
			//if right has a value go deeper into the tree recursively
			if ((*tree)->right != NULL)
			{
				insertInteger(&(*tree)->right, value);
			}
			//else set right to value
			else
			{
				(*tree)->right = new node;
				(*tree)->right->value = value;

				//initialise the left and right branches of the node to NULL
				(*tree)->right->left = NULL;
				(*tree)->right->right = NULL;
			}
		}
	}
}

void BinarySearchTree::printTree(node* tree)
{
	if (tree == NULL)
	{
		return;
	}

	printTree(tree->left);
	cout << tree->value << ' ';
	printTree(tree->right);
}

void BinarySearchTree::terminateTree(node* tree)
{
	if (tree != NULL)
	{
		terminateTree(tree->left);
		terminateTree(tree->right);
		delete tree;
	}
}


bool BinarySearchTree::searchTree(node* tree, int value)
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
