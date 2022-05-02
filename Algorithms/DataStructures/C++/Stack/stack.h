#pragma once
#include <iostream>

class Stack {

	struct item {
		int value;
		item* previous;
	};

	item* topItem;

public:
	void push(int val);
	void pop();
	void print() const;
	int top() const;
	bool isEmpty() const;

	Stack();
	~Stack();
};

