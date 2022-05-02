#include <iostream>
#include <list>

class HashTable {
private:
	static const int hashGroups = 10;
	std::list<std::pair<int, std::string>> table[hashGroups];

public:
	bool isEmpty() const;
	int  hashFunction(int key);
	void insertItem(int key, std::string value);
	void removeItem(int key);
	std::string searchTable(int key);
	void printTable();
};

bool HashTable::isEmpty() const {
	int sum{};
	for (int i{}; i < hashGroups; i++) {
		sum += table[i].size();
	}
	if (!sum)
		return true;
	else
		return false;
}

int HashTable::hashFunction(int key) {
	return key % hashGroups;
}

void HashTable::insertItem(int key, std::string value) {
	int hashValue = hashFunction(key);
	auto& cell = table[hashValue];
	bool keyExists = false;

	for (auto bItr = begin(cell); bItr != end(cell); bItr++)
		if (bItr->first == key) {
			keyExists = true;
			bItr->second = value;
			std::cout << "[WARNING] Key exists! Value replaced.\n";
			break;
		}

	if (!keyExists)
		cell.emplace_back(key, value);

	return;
}

void HashTable::removeItem(int key) {
	int hashValue = hashFunction(key);
	auto& cell = table[hashValue];
	bool keyExists = false;

	for (auto bItr = begin(cell); bItr != end(cell); bItr++)
		if (bItr->first == key) {
			keyExists = true;
			bItr = cell.erase(bItr);
			std::cout << "[INFO] Item removed!\n";
			break;
		}
	if (!keyExists)
		std::cout << "[WARNING] Key not found. Pair not removed!.\n";
	return;
}

void HashTable::printTable() {
	for (int i{}; i < hashGroups; i++) {
		if (table[i].size() == 0)
			continue;

		for (auto bItr = table[i].begin(); bItr != table[i].end(); bItr++) 
			std::cout << "[INFO] Key: " << bItr->first << " Value: " << bItr->second << std::endl;	
	}
}






int main() {
	HashTable HT;

	if (HT.isEmpty())
		std::cout << "Correct\n";
	else
		std::cout << "uhoh stinky\n";

	HT.insertItem(905, "Jim");
	HT.insertItem(201, "Tom");
	HT.insertItem(332, "Bob");
	HT.insertItem(124, "Sally");
	HT.insertItem(107, "Sandy");
	HT.insertItem(929, "Rob");
	HT.insertItem(928, "Rick");

	HT.printTable();

	HT.removeItem(332);
	HT.removeItem(100);


	if (HT.isEmpty())
		std::cout << "uhoh stinky\n";
	else
		std::cout << "nice\n";

}