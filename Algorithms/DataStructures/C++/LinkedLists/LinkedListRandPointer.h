#pragma once
#include <iostream>


class LinkedListRandPointer {

	typedef struct node {
	int data;
	node *next, *random;
	node() = default;
	node(int data) {
		this->data = data;
		this->next = this->random = nullptr;
	}
} *nodePtr; // instead of using node* we can use nodePtr - typedef


nodePtr head, curr, temp;

public:
	LinkedListRandPointer();
	~LinkedListRandPointer();

	LinkedListRandPointer(const LinkedListRandPointer& owner);
	LinkedListRandPointer(nodePtr head) { this->head = head; }

	void addNode(int addData);
	void deleteNode(int delData);
	void printList();
	int getListSize();
	void linkRandomPointers();
	void printWithRandom();

	LinkedListRandPointer* clone();
};

