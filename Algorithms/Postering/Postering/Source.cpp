#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

void MySolution();
void FindSubGroup(std::vector<int>& group);

void ResearchedSolution();
void ProcessHeight(std::stack<int>& heightsContainer, int height, int& sol);


//Could be static instead - used in MySolution
int poster_test = 0;

int main() {
	/* Exceeds memory requirements*/
	//MySolution();
	
	/*100 result*/
	ResearchedSolution();
	return 0;
}

void MySolution() {
	std::ios_base::sync_with_stdio(false);

	int amount, skip, height;
	std::cin >> amount;
	std::vector<int> numbers;
	numbers.reserve(amount);

	for (int i = 0; i < amount; ++i) {
		std::cin >> skip;
		std::cin >> height;
		numbers.push_back(height);
	}
	FindSubGroup(numbers);
	std::cout << poster_test;
}


/*
What are subgroups:
	0 0 2 1 2 0 0 1
	Subgroups: 2 1 2, 1;
*/

void FindSubGroup(std::vector<int>& group) {

	/* First pass is always valid - no '0' heights. Find lowest building, cover every build at that height */
	int min = *std::min_element(group.begin(), group.end());
	std::transform(group.begin(), group.end(), group.begin(), [min](int value) {return value - min; });
	++poster_test;
	int max = *std::max_element(group.begin(), group.end());

	//If entire group height is equal 0, then there is nothing more to cover
	if (max == 0) {
		return;
	}
	else {
		std::vector<int>::iterator iterator = group.begin();
		std::vector<int>::iterator last = group.begin(), begin = group.begin();

		// Pass through the entire size
		while (iterator != group.end()) {

			// Find first non zero number
			int distanceToNum = std::distance(iterator, find_if(iterator, group.end(), [](int x) { return x != 0; }));
			iterator += distanceToNum;

			if (iterator == group.end())
				return;
			last = iterator;

			// Find the end of the subgroup (last number before a 0)
			int distanceToZero = std::distance(last, find_if(last, group.end(), [](int x) { return x == 0; })) - 1;
			if (distanceToZero > 0 && distanceToZero < group.size())
				last += distanceToZero;
			else
				last = iterator;


			std::vector<int> subgroup(iterator, last + 1);
			FindSubGroup(subgroup);

			// Find another subgroup 
			iterator = last + 1;
		}
	}
}



void ResearchedSolution() {

	std::ios_base::sync_with_stdio(false);
	std::stack<int> heightsContainer;

	int amount, solution = 0;
	std::cin >> amount;

	for (int i = 0; i < amount; i++) {
		int dontcare, height;
		std::cin >> dontcare >> height;

		ProcessHeight(heightsContainer, height, solution);
	}

	std::cout << solution + heightsContainer.size() << std::endl;
}

void ProcessHeight(std::stack<int>& heightsContainer, int height, int& sol) {
	while (!heightsContainer.empty()) {

		if (heightsContainer.top() < height) {
			heightsContainer.push(height);
			return;
		}
		else if (heightsContainer.top() == height)
			return;
		else {
			heightsContainer.pop();
			++sol;
		}
	}

	heightsContainer.push(height);
}
