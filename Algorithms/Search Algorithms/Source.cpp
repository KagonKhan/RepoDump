#include <iostream>
#include <vector>

//Time complexity O(n)
int linearSearch(std::vector<int>& arr, int num) {
	for (int i = 0; i < arr.size(); ++i)
		if (arr[i] == num)
			return i;
	return -1;
}

//Time complexity O(log n) if the array is sorted
int recursiveBinarySearch(std::vector<int>& arr, int l, int r, int num) {
	int mid = l + (r - l) / 2;

	if (arr[mid] == num)
		return mid+1;
	if (arr[mid] < num)
		recursiveBinarySearch(arr, mid + 1, r, num);
	if (arr[mid] > num)
		recursiveBinarySearch(arr, l, mid - 1, num);

	return -1;
}





int main() {
	std::vector<int> test = { 2, 3, 4, 10, 40 };
	std::cout << recursiveBinarySearch(test, 0, test.size(), 4);



	return 0;
}