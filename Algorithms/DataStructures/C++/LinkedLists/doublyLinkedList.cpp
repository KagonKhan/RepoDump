#include "doublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList() {
	head = curr = temp = tail = nullptr;
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& original) {
	head = temp = curr = nullptr;

	nodePtr origin = original.head;

	while (origin) {
		addNode(origin->data);
		origin = origin->next;
	}

}

DoublyLinkedList::~DoublyLinkedList() {
}

void DoublyLinkedList::addNode(int addData) {
	nodePtr newNode = new node;
	newNode->data = addData;
	newNode->prev = newNode->next = nullptr;
	
	if (!head) {
		head = newNode;
		tail = newNode;
		return;
	}

	curr = head;
	while (curr->next)
		curr = curr->next;

	curr->next = newNode;
	newNode->prev = curr;
	tail = newNode;
}

void DoublyLinkedList::deleteNode(int delData) {
	if (!head) {
		std::cout << "List is empty!\n";
		return;
	}

	curr = head;
	nodePtr delPtr;

	while (curr && curr->data != delData) {
		temp = curr;
		curr = curr->next;
	}

	if (!curr) {
		std::cout << delData << " not found!\n";
		return;
	}

	delPtr = curr;

	if (delPtr == tail) {
		temp->next = nullptr;
		delete delPtr;
		return;
	}

	if (delPtr == head) {
		head = head->next;
		head->prev = nullptr;
		delete delPtr;
		return;
	}

	temp->next = curr->next;
	curr->next->prev = temp;


	curr->next = curr->prev = nullptr;
	delete delPtr;

}

void DoublyLinkedList::printList() {
	if (!head) {
		std::cout << "List empty!\n";
		return;
	}
	curr = head;
	while (curr) {
		std::cout << curr->data << " key\n";
		curr = curr->next;
	}
}
