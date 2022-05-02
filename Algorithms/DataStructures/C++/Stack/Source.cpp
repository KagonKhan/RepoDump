#include "stack.h"
#include <stack>


int main() {

	Stack myStack;

	std::cout << myStack.top();

	for (int i = 0; i <= 10; i++)
		myStack.push(i);
	std::cout << "\n" <<  myStack.top() << "\n";

}