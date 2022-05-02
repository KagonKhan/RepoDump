#pragma once
#include <iostream>


class LinkedList {
	typedef struct node {
		int data;
		node* next;
	} *nodePtr; // instead of using node* we can use nodePtr - typedef


	nodePtr head, curr, temp;

public:
	LinkedList();
	~LinkedList();

	LinkedList(const LinkedList& owner);


	void addNode(int addData);
	void deleteNode(int delData);
	const void printList() ;

};

