#include "BinarySearchTree.h"



BinarySearchTree::BinarySearchTree()
{
}

BinarySearchTree::~BinarySearchTree()
{
	terminateTree(root);
}

void BinarySearchTree::insertInteger(struct node** tree, int value)
{
	if (root == NULL)
	{
		root = new node;
		root->value = value;
		root->left = NULL;
		root->right = NULL;
	}
	else
	{
		if (value < (*tree)->value)
		{
			if ((*tree)->left != NULL)
			{
				insertInteger(&(*tree)->left, value);
			}
			else
			{
				(*tree)->left = new node;
				(*tree)->left->value = value;
				(*tree)->left->left = NULL;
				(*tree)->left->right = NULL;
			}
		}
		else if (value >= (*tree)->value)
		{
			if ((*tree)->right != NULL)
			{
				insertInteger(&(*tree)->right, value);
			}
			else
			{
				(*tree)->right = new node;
				(*tree)->right->value = value;
				(*tree)->right->left = NULL;
				(*tree)->right->right = NULL;
			}
		}
	}
}

void BinarySearchTree::printTree(struct node* tree)
{
	if (tree == NULL)
	{
		return;
	}

	printTree(tree->left);
	std::cout << tree->value << std::endl;
	printTree(tree->right);
}

void BinarySearchTree::terminateTree(struct node* tree)
{
	if (tree != NULL)
	{
		terminateTree(tree->left);
		terminateTree(tree->right);
		delete tree;
	}
}
