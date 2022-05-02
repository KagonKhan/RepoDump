#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <fstream>
#include <functional>
using namespace std::chrono;
//#include <iostream>

#pragma region function prototypes

template <class T>
int partition(std::vector<T>* partArray, int left, int right, T pivot);

template<class T>
void sort_quicksort_first(std::vector<T>* sortArray);
template<class T>
void sort_quicksort_first(std::vector<T>* sortArray, int left, int right);

template <class T>
void sort_quicksort_median(std::vector<T>* sortArray);
template <class T>
void sort_quicksort_median(std::vector<T>* sortArray, int left, int right);

template <class T>
void sort_quicksort_rand(std::vector<T>* sortArray);
template <class T>
void sort_quicksort_rand(std::vector<T>* sortArray, int left, int right);


template <class T>
void sort_quicksort_insertion(std::vector<T>* sortArray);
template <class T>
void sort_quicksort_insertion(std::vector<T>* sortArray, int left, int right);
template <class T>
void insertionSort(std::vector<T>* sortArray, int left, int right);



template <class T>
void sort_shellsort(std::vector<T>* sortArray);
template <class T>
void sort_shellsort_exp(std::vector<T>* sortArray);

std::vector<std::string> _2kWords;
std::vector<std::string> _4kWords;
std::vector<std::string> _8kWords;
std::vector<std::string> _16kWords;
std::vector<std::string> _32kWords;

std::vector<int> _8kNums;
std::vector<int> _16kNums;
std::vector<int> _32kNums;
std::vector<int> _64kNums;
std::vector<int> _128kNums;

#pragma endregion


template <class T>
int check_if_sorted(std::vector<T>* sortArray) {
	int N = sortArray->size();
	int i = 1;
	int is_sorted = 1;
	while ((i < N) && is_sorted) {
		if ((*sortArray)[i - 1] > (*sortArray)[i])
			is_sorted = 0;
		i++;
	}
	return (is_sorted);
}

// =================================   SELECTION   ===================================
template <class T>
void sort_selection(std::vector<T>& sortArray, bool ascending = true) {
	unsigned int size = sortArray.size();
	if (size == 0)
		throw std::runtime_error("empty array");

	unsigned int index;

	for (unsigned int i = 0; i < size - 1; i++) {
		index = i;

		for (unsigned int j = i + 1; j < size; j++) {
			if (ascending)
				if (sortArray[j] < sortArray[index])
					index = j;
			if (!ascending)
				if (sortArray[j] > sortArray[index])
					index = j;

		}
		if (sortArray[index] != sortArray[i])
			std::swap(sortArray[i], sortArray[index]);
	}

	return;
}


//apologies for this
template <class T>
void sort_stableSelection(std::vector<T>& sortArray, bool ascending = true) {
	unsigned int size = sortArray.size();
	if (!size)
		throw std::runtime_error("empty array");

	for (unsigned int i = 0; i < size - 1; ) {
		unsigned int index = i;

		for (unsigned int j = i + 1; j < size; j++) {
			if (ascending)
				if (sortArray[j] < sortArray[index])
					index = j;
			if (!ascending)
				if (sortArray[j] > sortArray[index])
					index = j;
		}


		T keepValue = sortArray[index];
		while (index > i)
			sortArray[index] = sortArray[index-- - 1];

		sortArray[i++] = keepValue;
	}
	return;
}


// =================================   INSERTION   ===================================

template <class T>
void sort_insertion(std::vector<T>& sortArray, bool ascending = true) {
	unsigned int size = sortArray.size();
	if (size == 0)
		throw std::runtime_error("empty array");

	for (unsigned int i = 1; i < size; i++) {
		T current = sortArray[i];

		int j = i - 1;
		while (j >= 0 && sortArray[j] > current)
			sortArray[j + 1] = sortArray[j--];

		sortArray[j + 1] = current;
	}

}

template <class T>
int binarySearch(std::vector<T>& a, T key, int left, int right) {
	int mid = (left + right) / 2;

	int x[10];
	for (int i = 0; i < 10; i++)
		x[i] = 6;

	if (key == a[mid])
		return mid;

	if (right <= left)
		return (key > a[left]) ? (left + 1) : left;


	if (key > a[mid])
		return binarySearch(a, key, mid + 1, right);

	return binarySearch(a, key, left, mid - 1);
}

template <class T>
void sort_binaryInsertion(std::vector<T>& sortArray, bool ascending = true) {
	unsigned int size = sortArray.size();
	if (size == 0)
		throw std::runtime_error("empty array");

	for (unsigned int i = 1; i < size; i++) {
		T current = sortArray[i];

		int j = i - 1;
		int index = binarySearch(sortArray, current, 0, j);

		while (j >= index) {
			sortArray[j + 1] = sortArray[j];
			j--;
		}

		sortArray[j + 1] = current;
	}
}

// =================================   BUBBLE   ===================================
template <class T>
void sort_bubble(std::vector<T>& sortArray, bool ascending = true) {
	unsigned int size = sortArray.size();

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (ascending)
				if (sortArray[j] > sortArray[j + 1])
					std::swap(sortArray[j], sortArray[j + 1]);
			if (!ascending)
				if (sortArray[j] < sortArray[j + 1])
					std::swap(sortArray[j], sortArray[j + 1]);
		}
	}
}

template <class T>
void sort_cocktailBubble(std::vector<T>& sortArray, bool ascending = true) {
	unsigned int size = sortArray.size();

	bool swapped = true;
	int start = 0;
	int end = size - 1;

	while (swapped) {

		swapped = false;

		// loop from left to right same as
		// the bubble sort
		for (int i = start; i < end; ++i) {
			if (sortArray[i] > sortArray[i + 1]) {
				std::swap(sortArray[i], sortArray[i + 1]);
				swapped = true;
			}
		}

		if (!swapped)
			break;

		swapped = false;
		--end;
		for (int i = end - 1; i >= start; --i) {
			if (sortArray[i] > sortArray[i + 1]) {
				std::swap(sortArray[i], sortArray[i + 1]);
				swapped = true;
			}
		}
		++start;
	}
}

template <class T>
void sort_storedBubble(std::vector<T>& sortArray, bool ascending = true) {
	int size = sortArray.size();


	for (int i = 0; i < size - 1; i++) {
		int last = 0;
		for (int j = 0; j < size - 1 - i; j++)
			if (sortArray[j] > sortArray[j + 1]) {
				last = j;
				std::swap(sortArray[j], sortArray[j + 1]);
			}
		i += size - 2 - i - last;
	}
}

// =================================   MAIN   ===================================


void loadIntoArrayFromDataVec_ints(std::vector<int>* data, std::vector<int>* loadn, std::vector<int>* load4n, std::vector<int>* load8n, std::vector<int>* load16n, std::vector<int>* load32n) {
	loadn->clear();
	load4n->clear();
	load8n->clear();
	load16n->clear();
	load32n->clear();

	int n = 128000;

	loadn->reserve(n);
	load4n->reserve(4 * n);
	load8n->reserve(8 * n);
	load16n->reserve(16 * n);
	load32n->reserve(32 * n);


	std::copy(data->begin(), data->begin() + n, std::back_inserter(*loadn));
	std::copy(data->begin(), data->begin() + 4 * n, std::back_inserter(*load4n));
	std::copy(data->begin(), data->begin() + 8 * n, std::back_inserter(*load8n));
	std::copy(data->begin(), data->begin() + 16 * n, std::back_inserter(*load16n));
	std::copy(data->begin(), data->begin() + 32 * n, std::back_inserter(*load32n));

}

void loadIntoArrayFromDataVec_strings(std::vector<std::string>* data, std::vector<std::string>* loadn, std::vector<std::string>* load4n, std::vector<std::string>* load8n, std::vector<std::string>* load16n, std::vector<std::string>* load32n) {
	loadn->clear();
	load4n->clear();
	load8n->clear();
	load16n->clear();
	load32n->clear();

	int n_str = 32000;

	loadn->reserve(n_str);
	load4n->reserve(4 * n_str);
	load8n->reserve(8 * n_str);
	load16n->reserve(16 * n_str);
	load32n->reserve(32 * n_str);


	std::copy(data->begin(), data->begin() + n_str,		 std::back_inserter(*loadn));
	std::copy(data->begin(), data->begin() + 2 * n_str,  std::back_inserter(*load4n));
	std::copy(data->begin(), data->begin() + 4 * n_str,  std::back_inserter(*load8n));
	std::copy(data->begin(), data->begin() + 16 * n_str, std::back_inserter(*load16n));
	std::copy(data->begin(), data->begin() + 32 * n_str, std::back_inserter(*load32n));

}

int main() {
	int n = 128000;
	int n_str = 32000;

#pragma region initialization

	std::vector<int> arr_int_128000(n);
	std::vector<int> arr_int_512000(4 * n);
	std::vector<int> arr_int_1024000(8 * n);
	std::vector<int> arr_int_2048000(16 * n);
	std::vector<int> arr_int_4096000(32 * n);

	std::vector<int> dataArray(4096000);
	std::generate(dataArray.begin(), dataArray.end(), [&n]() { return rand() % (50 * n); });


	std::vector<std::vector<int>*> intdata;

	intdata.reserve(5);

	intdata.emplace_back(&arr_int_128000);
	intdata.emplace_back(&arr_int_512000);
	intdata.emplace_back(&arr_int_1024000);
	intdata.emplace_back(&arr_int_2048000);
	intdata.emplace_back(&arr_int_4096000);


	std::vector<std::string> arr_string_32000(n);
	std::vector<std::string> arr_string_64000(2 * n);
	std::vector<std::string> arr_string_128000(4 * n);
	std::vector<std::string> arr_string_512000(16 * n);
	std::vector<std::string> arr_string_1024000(32 * n);

	std::vector<std::vector<std::string>*> stringdata;

	std::vector<std::string> dataArray_str(32 * n);
	std::generate(dataArray_str.begin(), dataArray_str.end(), [&n]() {
		std::string text = "";
		for (int i = 0; i < rand() % 10 + 5; i++)
			text += (char)rand() % (26) + 'A';
		return text;
		});

	stringdata.emplace_back(&arr_string_32000);
	stringdata.emplace_back(&arr_string_64000);
	stringdata.emplace_back(&arr_string_128000);
	stringdata.emplace_back(&arr_string_512000);
	stringdata.emplace_back(&arr_string_1024000);

	

	std::chrono::milliseconds string_times[6][5]{ (std::chrono::milliseconds)0 };
	std::chrono::milliseconds int_times[6][5]{ (std::chrono::milliseconds)0 };
	auto start = high_resolution_clock::now();
	auto end = high_resolution_clock::now();





	
	void (*int_functions[]) (std::vector<int>*) = { sort_quicksort_first, sort_quicksort_rand, sort_quicksort_median, sort_quicksort_insertion, sort_shellsort, sort_shellsort_exp };
	void (*string_functions[]) (std::vector<std::string>*) = { sort_quicksort_first, sort_quicksort_rand, sort_quicksort_median, sort_quicksort_insertion, sort_shellsort, sort_shellsort_exp };


#pragma endregion


	for (int i = 0; i < 6; i++) {
		loadIntoArrayFromDataVec_ints(&dataArray, &arr_int_128000, &arr_int_512000, &arr_int_1024000, &arr_int_2048000, &arr_int_4096000);
		loadIntoArrayFromDataVec_strings(&dataArray_str, &arr_string_32000, &arr_string_64000, &arr_string_128000, &arr_string_512000, &arr_string_1024000);

		for (int j = 0; j < 5; j++) {
			start = high_resolution_clock::now();
			(*int_functions[i]) (intdata[j]);
			end = high_resolution_clock::now();
			int_times[i][j] = duration_cast<milliseconds>(end - start);

			//if (!check_if_sorted(intdata[j]))
			//	return -1;

			start = high_resolution_clock::now();
			(*string_functions[i]) (stringdata[j]);
			end = high_resolution_clock::now();
			string_times[i][j] = duration_cast<milliseconds>(end - start);


			//if (!check_if_sorted(stringdata[j]))
			//	return -1;
		}
	}
	

	std::ofstream results("results.csv");


	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++)
			results << int_times[i][j].count()/1000.0 << "\t";
		results << "\n";
	}
	results << "\n";

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++)
			results << string_times[i][j].count()/1000.0 << "\t";
		results << "\n";
	}
	results.close();

	return 0;
}




template<class T>
int partition(std::vector<T>* partArray, int left, int right, T pivot) {

	while (left <= right) {
		while ((*partArray)[left] < pivot)
			left++;
		while ((*partArray)[right] > pivot)
			right--;

		if (left <= right) {
			std::swap((*partArray)[left], (*partArray)[right]);
			left++; right--;

		}
	}
	return left;
}

template <class T>
void sort_shellsort(std::vector<T>* sortArray) {
	int n = sortArray->size();

	for (int h = n / 2; h > 0; h /= 2)
		for (int i = h; i < n; i++) {
			T curr = (*sortArray)[i];
			int j;
			for (j = i; j >= h && (*sortArray)[j - h] > curr; j -= h)
				(*sortArray)[j] = (*sortArray)[j - h];
			(*sortArray)[j] = curr;
		}

}
template <class T>
void sort_shellsort_exp(std::vector<T>* sortArray) {

	int n = sortArray->size(), h = 1, i;

	for (i = 1; h < n; i++)
		h = (1 << i) - 1;

	while (i > 0) {
		i--;

		int h = (1 << i) - 1;

		for (int i = h; i < n; i++) {
			T curr = (*sortArray)[i];
			int j;
			for (j = i; j >= h && (*sortArray)[j - h] > curr; j -= h)
				(*sortArray)[j] = (*sortArray)[j - h];
			(*sortArray)[j] = curr;
		}
	}
}

template <class T>
void sort_quicksort_median(std::vector<T>* sortArray) {
	sort_quicksort_median(sortArray, 0, sortArray->size() - 1);
}
template <class T>
void sort_quicksort_median(std::vector<T>* sortArray, int left, int right) {
	if (left >= right)
		return;

	T arr[3];
	arr[0] = (*sortArray)[left];
	arr[1] = (*sortArray)[right];
	arr[2] = (*sortArray)[(left + right) / 2];

	for (unsigned int i = 0; i < 2; i++) {
		int	index = i;

		for (unsigned int j = i + 1; j < 3; j++) {
			if (arr[j] < arr[index])
				index = j;
		}
		if (arr[index] != arr[i])
			std::swap(arr[i], arr[index]);
	}

	T pivot = arr[1];


	int index = partition(sortArray, left, right, pivot);

	sort_quicksort_median(sortArray, left, index - 1);
	sort_quicksort_median(sortArray, index, right);
}

template <class T>
void sort_quicksort_first(std::vector<T>* sortArray) {
	sort_quicksort_first(sortArray, 0, sortArray->size() - 1);
}
template<class T>
void sort_quicksort_first(std::vector<T>* sortArray, int left, int right) {
	if (left >= right)
		return;

	T pivot = (*sortArray)[left];
	int index = partition(sortArray, left, right, pivot);

	sort_quicksort_first(sortArray, left, index - 1);
	sort_quicksort_first(sortArray, index, right);

}

template <class T>
void sort_quicksort_rand(std::vector<T>* sortArray) {
	sort_quicksort_rand(sortArray, 0, sortArray->size() - 1);
}
template <class T>
void sort_quicksort_rand(std::vector<T>* sortArray, int left, int right) {
	if (left >= right)
		return;

	T pivot = (*sortArray)[rand() % (right - left) + left];
	int index = partition(sortArray, left, right, pivot);

	sort_quicksort_rand(sortArray, left, index - 1);
	sort_quicksort_rand(sortArray, index, right);

}
template<class T>
void sort_quicksort_insertion(std::vector<T>* sortArray) {
	sort_quicksort_insertion(sortArray, 0, sortArray->size() - 1);
}

template<class T>
void sort_quicksort_insertion(std::vector<T>* sortArray, int left, int right) {
	if ((right - left) < 9)
		insertionSort(sortArray, left, right);
	else {
		T pivot = (*sortArray)[(left + right) / 2];
		int index = partition(sortArray, left, right, pivot);

		sort_quicksort_insertion(sortArray, left, index - 1);
		sort_quicksort_insertion(sortArray, index, right);
	}
}

template<class T>
void insertionSort(std::vector<T>* sortArray, int left, int right) {
	unsigned int size = sortArray->size();
	if (size == 0)
		throw std::runtime_error("empty array");

	for (unsigned int i = left; i < right; i++) {
		T current = (*sortArray)[i];

		int j = i - 1;
		while (j >= 0 && (*sortArray)[j] > current)
			(*sortArray)[j + 1] = (*sortArray)[j--];

		(*sortArray)[j + 1] = current;
	}

}
