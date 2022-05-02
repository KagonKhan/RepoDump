#pragma once
#include <iostream>

class DoublyLinkedList {
	typedef struct node {
		int data;
		node *prev, *next;
	}* nodePtr;
	nodePtr head, curr, temp, tail;
public:
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList& original);
	~DoublyLinkedList();
	
	void addNode(int addData);
	void deleteNode(int delData);
	void printList();


};

