#pragma once
#include <vector>
#include <iostream>


class BST {
	struct node {
		int data;
		node *left, *right;
	};

	node* root;

	void printInOrderPrivate(node* ptr);
	void addLeafPrivate(int data, node* ptr);



public:
	BST();
	BST(int data);
	BST(const std::vector<int>& data);

	node* createLeaf(int data);
	void addLeaf(int data);
	void addLeaf(const std::vector<int>& data);
	void printInOrder();

};

