#include "BST.h"

int main() {
	std::vector<int> treeKeys = { 50, 76, 21, 4, 32, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80 };

	BST tree;
	tree.addLeaf(treeKeys);

	tree.printInOrder();



}