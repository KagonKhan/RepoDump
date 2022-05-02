#include "BST.h"

void BST::printInOrderPrivate(node* ptr) {
	if (!root) {
		std::cout << "Tree empty!\n";
		return;
	}

	if (ptr->left)
		printInOrderPrivate(ptr->left);
	std::cout << ptr->data << ' ';

	if (ptr->right)
		printInOrderPrivate(ptr->right);
}

BST::BST() {
	root = nullptr;
}

BST::BST(int data) {
	root = createLeaf(data);
}

BST::BST(const std::vector<int>& data) {
	root = nullptr;

	for (int x : data)
		addLeaf(x);
}

BST::node* BST::createLeaf(int data) {
	node* newNode = new node;
	newNode->data = data;
	newNode->left = newNode->right = nullptr;
	return newNode;
}

void BST::addLeaf(int data) {
	addLeafPrivate(data, root);
}

void BST::addLeaf(const std::vector<int>& data) {
	for (int x : data)
		addLeafPrivate(x, root);
}

void BST::addLeafPrivate(int data, node* ptr) {
	if (!root) {
		root = createLeaf(data);
		return;
	}

	if (data < ptr->data) {
		if (ptr->left)
			addLeafPrivate(data, ptr->left);
		else
			ptr->left = createLeaf(data);
	}

	else if (data > ptr->data) {
		if (ptr->right)
			addLeafPrivate(data, ptr->right);
		else
			ptr->right = createLeaf(data);
	}

	else 
		std::cout << "Duplicates!\n";
	
}

void BST::printInOrder() {
	printInOrderPrivate(root);
}
