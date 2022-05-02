#include "LinkedList.h"
#include "doublyLinkedList.h"
#include "LinkedListRandPointer.h"

int main() {

	LinkedListRandPointer myList;

	myList.addNode(0);
	myList.addNode(1);
	myList.addNode(2);
	myList.addNode(3);
	myList.addNode(4);

	myList.printList();

	myList.linkRandomPointers();
	
	myList.printWithRandom();

	std::cout << std::endl;

	LinkedListRandPointer* clone = myList.clone();
	clone->printWithRandom();

	myList.deleteNode(4);
	clone->printWithRandom();

	return 0;
}