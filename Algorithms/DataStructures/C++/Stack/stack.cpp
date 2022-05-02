#include "stack.h"

Stack::Stack() {
	topItem = nullptr;
}

Stack::~Stack() {
	item* itemPtr1, * itemPtr2;
	itemPtr1 = topItem;

	while (itemPtr1) {
		itemPtr2 = itemPtr1;
		itemPtr1 = itemPtr1->previous;
		itemPtr2->previous = nullptr;
		std::cout << "Deleting " << itemPtr2->value << " value\n";
		delete itemPtr2;
	}
}


void Stack::push(int val) {
	item* newItem = new item;
	newItem->value = val;

	if (!topItem) {
		topItem = newItem;
		topItem->previous = nullptr;
	}
	else {
		newItem->previous = topItem;
		topItem = newItem;

	}

}

void Stack::pop() {
	if (!topItem) {
		std::cout << "Stack empty!\n";
		return;
	}

	item* delPtr = topItem;
	topItem = topItem->previous;
	std::cout << "Deleting " << delPtr->value << " value!\n";
	delPtr->previous = nullptr;
	delete delPtr;
}

void Stack::print() const {
	if (!topItem) {
		std::cout << "Stack empty!\n";
		return;
	}

	item* currItemPtr = topItem;
	
	while (currItemPtr) {
		std::cout << currItemPtr->value << ' ';
		currItemPtr = currItemPtr->previous;
	}

}


int Stack::top() const {
	if (topItem)
		return topItem->value;
	else {
		std::cout << "Stack is empty!\n";
		return -99999;
	}
}

bool Stack::isEmpty() const {
	if (topItem)
		return true;
	return false;
}

