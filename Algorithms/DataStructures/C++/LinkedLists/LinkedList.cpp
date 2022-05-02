#include "LinkedList.h"

LinkedList::LinkedList() {
	head = curr = temp = nullptr;
}

LinkedList::~LinkedList() {
}

LinkedList::LinkedList(const LinkedList& owner) {
	this->head = this->temp = this->curr = nullptr;

	nodePtr test = owner.head;

	while (test) {
		this->addNode(test->data);
		test = test->next;
	}
	test = nullptr;
}

void LinkedList::addNode(int addData) {
	nodePtr newNode = new node;
	newNode->data = addData;
	newNode->next = nullptr;


	if (!head) {
		head = newNode;
		return;
	}


	curr = head;
	while (curr->next)
		curr = curr->next;

	curr->next = newNode;
}

void LinkedList::deleteNode(int delData) {
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




const void LinkedList::printList()  {

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
