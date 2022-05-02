#include "LinkedListRandPointer.h"
#include <time.h>
#include <unordered_map>

LinkedListRandPointer::LinkedListRandPointer() {
	head = curr = temp = nullptr;
}

LinkedListRandPointer::~LinkedListRandPointer() {
}

LinkedListRandPointer::LinkedListRandPointer(const LinkedListRandPointer& owner) {
	this->head = this->temp = this->curr = nullptr;

	nodePtr test = owner.head;

	while (test) {
		this->addNode(test->data);
		test = test->next;
	}
	test = nullptr;
}

void LinkedListRandPointer::addNode(int addData) {
	nodePtr newNode = new node;
	newNode->data = addData;
	newNode->next = nullptr;
	newNode->random = nullptr;

	if (!head) {
		head = newNode;
		return;
	}


	curr = head;
	while (curr->next)
		curr = curr->next;

	curr->next = newNode;
}

void LinkedListRandPointer::deleteNode(int delData) {
	if (!head) {
		std::cout << "List empty!\n";
		return;
	}

	nodePtr delPtr = nullptr;

	curr = temp = head;
	while (curr && curr->data != delData) {
		temp = curr;
		curr = curr->next;
	}

	if (!curr) {
		std::cout << delData << " was not found in the list!\n";
		delete delPtr;
		return;
	}

	delPtr = curr;
	temp->next = curr->next;

	if (curr == head)
		head = head->next;

	std::cout << "Deleting " << delPtr->data << " data!\n";

	curr->next = nullptr;
	temp = nullptr;

	delete delPtr;

}

void LinkedListRandPointer::printList() {
	if (!head) {
		std::cout << "List empty!\n";
		return;
	}

	curr = head;

	while (curr) {
		std::cout << "Data: " << curr->data << "\n";
		curr = curr->next;
	}
}

int LinkedListRandPointer::getListSize() {
	curr = head;
	int counter = 0;
	while (curr) {
		counter++;
		curr = curr->next;
	}
	return counter;
}

void LinkedListRandPointer::linkRandomPointers() {

	if (!head)
		return;

	srand(time(NULL));

	int size = getListSize();

	curr = head;
	temp = head;

	while (curr) {
		int lim = rand() % size;

		for (int i = 0; i <= lim; i++) 
			if (temp->next) 
				temp = temp->next;
			
		curr->random = temp;
		curr = curr->next;
		temp = head;
	}
}

void LinkedListRandPointer::printWithRandom() {
	curr = head;
	while (curr) {
		if (curr->random) {
			std::cout << "I'm pointing to: " << curr->random->data << std::endl;
		} else { std::cout << "I'm pointing to nullptr!\n"; }

		curr = curr->next;
	}
}

LinkedListRandPointer* LinkedListRandPointer::clone() {
	nodePtr origCurr = head;
	nodePtr cloneCurr = nullptr;

	std::unordered_map<nodePtr, nodePtr> myMap;
	
	while (origCurr) {
		cloneCurr = new node(origCurr->data);
		myMap[origCurr] = cloneCurr;
		origCurr = origCurr->next;
	}

	origCurr = head;

	while (origCurr) {
		cloneCurr = myMap[origCurr];
		cloneCurr->next = myMap[origCurr->next];
		cloneCurr->random = myMap[origCurr->random];

		origCurr = origCurr->next;
	}

	return new LinkedListRandPointer(myMap[head]);
}

