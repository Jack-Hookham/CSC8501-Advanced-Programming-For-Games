// *******************************************
// * New, Delete, the Stack and the Heap *
// *******************************************

// Summary
// -------
// Understand about allocating and freeing memory and
// the Stack versus the Heap

// New Concepts
// ------------
// Memory Allocation

#pragma once
#include <iostream>
#include <string>

#include "BinarySearchTree.h"

using namespace std;

int main() {

	// when we declare the variable 'a' we are telling the compiler
	// to create this variable in an area of memory called the 'stack'. Stack 
	// variables are sometimes referred to as 'local variables' because they
	// only exist within a certain scope (more on scope later)
	int a;

	// variables on the 'stack' can hold any predefined type, including pointers
	// so we can also declare pointers on the stack like so...
	int* b;

	// You have already seen how you can assign a variable on the stack to a value
	// with the assignment operator '='. Here we assign the stack variable 'a' to 
	// hold the value 100
	a = 100;

	// The 'new' keyword allows us to allocate memory on something called 
	// the 'heap' instead of the 'stack'. The keyword 'new' is provided by C++ 
	// to handle the creation of variables on the 'heap' for us. In order to use
	//'new' you must specify the type of variable to create so that the compiler
	// knows how much memory to allocate on the 'heap'. Using 'new' also 'returns' 
	// the memory address where the newly allocated memory is located, so you must
	// assign the result of 'new' to a pointer type. The type of pointer will usually 
	// match the type of memory allocated. 
	b = new int;

	// Now we have a pointer to an integer called 'b' which points to an address	
	// located in 'heap' memory. We say the pointer 'b' exists on the stack but the 
	// memory pointed to by 'b' exists on the heap
	cout << "The pointer b points to the memory address " << b << " located on the heap\n";

	// After calling 'new' the memory is initialised to zero
	// and we can verify this by dereferencing the pointer b	
	cout << "The value in memory location b is " << *b << "\n";

	// If we want to assign the newly created 'heap' memory to a value we
	// must dereference pointer 'b' and assign it to an integer value
	*b = a;

	// Now the area of 'heap' memory pointed to by 'b' contains a copy of the value
	// assigned to the stack variable 'a'. Two memory locations contain the value 
	// 100, one on the stack and the other on the heap 
	cout << "The value of stack variable a is " << a << "\n";
	cout << "The 'heap' memory pointed to by b contains " << *b << "\n";

	char c;
	c = 'a';

	string* s;
	s = new string("String");

	cout << "The value of stack variable c is " << c << "\n";
	cout << "The 'heap' memory pointed to by s contains " << *s << "\n";

	const int arrSize = 10;
	int* arr = new int[arrSize]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	cout << "\n";
	for (int i = 0; i < arrSize; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << "\n\n";

	// The memory containing 'stack' variables is automatically 'released' 
	// when the program execution leaves their 'scope'. Variables allocated on the
	// 'heap' however are not automatically released like 'stack' variables. 
	// it is very important that the programmer releases 'heap' memory when finished
	// with it or else the memory cannot be reused and a 'memory leak' will be created. 
	// C++ provides the keyword 'delete' for this task which expects a pointer to 
	// a memory address on the 'heap'...
	delete b;
	delete s;
	delete[] arr;

	// when delete it called on a pointer variable it is good programming practise
	// to set the pointer to NULL. If you subsequently try to access a pointer that 
	// has been 'freed' with 'delete' you will probably cause your program to crash
	b = NULL;
	s = NULL;
	arr = NULL;

	// having reached the end of the function, the stack variables 'int a' and 'int* b'
	// will be automatically released. If you had not released the 'heap' memory previously
	// pointed to by 'b' it would have be lost for the duration of the program execution
	// always remember to free memory allocated with 'new' once you are finished with it,
	// by calling 'delete' on the pointer which points to it! 

	BinarySearchTree bst;
	bst.insertInteger(&bst.root, 10);
	bst.insertInteger(&bst.root, 5);
	bst.insertInteger(&bst.root, 11);
	bst.insertInteger(&bst.root, 16);
	bst.insertInteger(&bst.root, 1);
	bst.insertInteger(&bst.root, 2);

	bst.printTree(bst.root);

	bst.terminateTree(bst.root);
	cin.ignore();
	cin.get();

	return 0;
}

/* Program without comments:

#include <iostream>

using namespace std;

int main () {

int a;

int* b;

a = 100;

b = new int;

cout << "The pointer b points to the memory address " << b << " located on the heap\n";
cout << "The value in memory location b is " << *b << "\n";

*b = a;

cout << "The value of stack variable a is " << a << "\n";
cout << "The 'heap' memory pointed to by b contains " << *b << "\n";

delete b;
b = NULL;

return 0;
}

*/


