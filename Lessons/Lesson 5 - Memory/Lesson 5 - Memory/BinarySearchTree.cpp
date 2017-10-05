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
	if (*tree == NULL)
	{
		*tree = new node;
		(*tree)->value = value;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
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
	cout << tree->value << endl;
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

void BinarySearchTree::printPretty(struct node* tree)
{
	int height = getHeight(tree) * 2;

	for (int i = 0; i < height; i++)
	{
		printRow(tree, height, i);
	}
}

void BinarySearchTree::printRow(const node* tree, const int height, int depth)
{
	int placeholder = 1 << 31;
	vector<int> vec;
	getLine(tree, depth, vec);

	cout << setw((height - depth) * 2);

	bool toggle = true;

	if (vec.size() > 1)
	{
		for (int v : vec)
		{
			if (v != placeholder)
			{
				if (toggle)
				{
					cout << "/" << "   ";
				}
				else
				{
					cout << "\\" << "   ";
				}
			}
			else
			{
				cout << "    ";
			}
			toggle = !toggle;
		}
		cout << "\n";
		cout << setw((height - depth) * 2);
	}
	for (int v : vec)
	{
		if(v != placeholder)
		{
			cout << v << "   ";
		}
		else
		{
			cout << "    ";
		}
	}
	cout << "\n";
}

void BinarySearchTree::getLine(const node* tree, int depth, vector<int>& values)
{
	int placeholder = 1 << 31;
	if (depth <= 0 && tree != NULL) 
	{
		values.push_back(tree->value);
		return;
	}
	if (tree->left != NULL)
	{
		getLine(tree->left, depth - 1, values);
	}
	else if (depth - 1 <= 0)
	{
		values.push_back(placeholder);
	}
	if (tree->right != NULL)
	{
		getLine(tree->right, depth - 1, values);
	}
	else if (depth - 1 <= 0)
	{
		values.push_back(placeholder);
	}
}

int BinarySearchTree::getHeight(node* tree)
{
	if (tree == NULL)
	{
		return 0;
	}
	else
	{
		int left = getHeight(tree->left);
		int right = getHeight(tree->right);

		if (left > right)
		{
			return left + 1;
		}
		else
		{
			return right + 1;
		}
	}
}

