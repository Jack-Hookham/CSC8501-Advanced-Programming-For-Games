// ************************************************
// * Program Scope and the life-time of variables *
// ************************************************

// Summary
// -------
// Understand about the different scopes in C++
// Programs and how this affects program variables

// New Concepts
// ------------
// Scope, Namespaces

#include <iostream>

using namespace std;

// C++ programs incorporate the notion of 'scope' and 'extent'. Scope creates 
// hierachical divisions between different sections of any C++ program, limiting 
// the extent of named variables within that scope. 
//
// One form of scope we have already seen exists with functions. The 
// extent (or existence) of local-variables is limited to the scope of a 
// function which we create using curly brackets {} at the beginning and at 
// the end of any function we define
//

namespace some_namespace
{
	void some_function() { // beginning of function scope

						   // stack variables declared within a function only exist for the duration 
						   // of its execution...
		int a = 400;
		char letter = 'b';

		cout << "a = " << a << "\n";
		cout << "letter = " << letter << "\n";

	} // end of function scope 
}

namespace some_other_namespace
{
	void some_function() { // beginning of function scope

						   // stack variables declared within a function only exist for the duration 
						   // of its execution...
		int a = 500;
		char letter = 'c';

		cout << "a = " << a << "\n";
		cout << "letter = " << letter << "\n";

	} // end of function scope 
}


  // We can declare global variables in C++ whose scope extends to the entire cpp file
  // Global variables exist for the duration of the program's execution
int global_variable = 50;

int main() { //entering the scope of the main function

			 // we are now in the scope of main, but we still have access to 'global_variable'. 
			 // Global scope encompasses the scope of main, which means we can (usually) access 
			 // variables from an encompassing scope...
	cout << "global variable contains the value " << global_variable << "\n";

	// Here we have the declaration of an integer variable 'a' and a pointer to an 
	// integer 'b' which are local to the scope of the main function. We will use these
	// to demonstrate the effects of scope and extent.
	int a = 100;
	int* b;

	// We can create a scoped block of code by inserting curly brackets
	// within a function. As with functions, we initiate a scoped-block with
	// the opening-bracket { and close it with the closing-bracket }
	{

		// on this line we have progressed from the scope of the main function to the scope
		// created by the opening-bracket. Note that 'scope' is hierarchical and an 'inner' 	
		// scope exists solely within the brackets of an 'outer' scope.

		// Notice now the 'extent' of stack-variables declared within a refined scope. 
		// Here we declare another variable called 'a' whose extent is limited to 	 
		// this local-scope (within the curly brackets). The naming of variable 'a' does not 	
		// cause a conflict with the previous variable 'a' declared outside this scope
		int a = 200;

		// when we output its value we see that it is 200
		cout << "the value in a is " << a << "\n";

		// if we allocate memory on the heap here we must be sure to release it before we leave this scope. 
		// (here we are using a constructor () to initialise the heap memory to the value 300; more on 
		// constructors later)
		int* local_ptr = new int(300);

		// Alternatively, we can use another pointer which will exist beyond the current scope to 
		// ensure the memory is not lost, the pointer 'b' for instance will continue to exist beyond this
		// scope...
		b = local_ptr;

	}

	// now we have returned to the scope of main function and any variables created
	// in the inner-scope no longer exist. We can see this by printing the value of 
	// variable 'a'. Note that the output shows 100. 
	cout << "the value in a is " << a << "\n";

	// the variable local_ptr has ceased to exist, but because we stored the memory address
	// in 'b' we can still access (and release) the heap memory allocated
	cout << "the value pointed to by 'b' is " << *b << "\n";
	delete b;
	b = NULL;

	// In C++ we also have something called the 'scope operator' denoted by a double colon :: 	
	// which comes into use with namespaces. We have already seen the command to tell the
	// compiler which namespace(s) we wish to use: 'using namespace std;'. This allows us to 
	// write 'cout' without the need to provide the namespace 'std' where the 'cout' function 
	// is defined. However, we could also have used the fully qualified expression...
	std::cout << "output some data" << "\n";

	// finally, when the program enters a function, the scope changes again to that of the local 
	// function. Although the function can reference global variables, the variables 'a' and 'b' 
	// will not be known to the function's local-scope. In this case we must 'pass' the variables
	// 'a' and 'b' to the function as parameters, if the function requires access to them (more on 
	// this in the next lesson)
	
	cout << "\n";
	some_namespace::some_function();
	some_other_namespace::some_function();

	// Three variables, same name, no conflict
	{
		int c = 10;
		cout << "\nc = " << c << "\n";
	}

	{
		int c = 20;
		cout << "c = " << c << "\n";
	}

	int c = 30;
	cout << "c = " << c << "\n";

	cin.ignore();
	cin.get();

	return 0;
}


/* Program without comments:

#include <iostream>

using namespace std;

int main () {

cout << "global variable contains the value " << global_variable << "\n";

int a = 100;
int* b;

{

int a = 200;

cout << "the value in a is " << a << "\n";

int* local_ptr = new int(300);

b = local_ptr;

}

cout << "the value in a is " << a << "\n";

cout << "the value pointed to by 'b' is " << *b << "\n";
delete b;
b = NULL;

std::cout << "output some data" << "\n";

some_function();

return 0;
}

*/


