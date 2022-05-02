#include <vector>
#include <iostream>
#include <string>
#include <functional>
#include <sstream>
#include <chrono>
#include <fstream>

int times[2][2];

std::string sub = "";

int ED_dynamic(const std::string& str1, const std::string& str2) {
	times[1][0] = 0;
	int size1 = str1.length() + 1, size2 = str2.length() + 1;
	std::vector<std::vector<int>> lengthTab(size1, std::vector<int>(size2, 0));
	sub = "";


	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			times[1][0]++;
			if (i == 0)	lengthTab[i][j] = j;
			else if (j == 0) lengthTab[i][j] = i; 

			else 
				lengthTab[i][j] = (str1[i - 1] == str2[j - 1]) ? lengthTab[i - 1][j - 1] : 1 + std::min(std::min(lengthTab[i][j - 1], lengthTab[i - 1][j]),	lengthTab[i - 1][j - 1]);
		}
	}
	std::stringstream str;
	for (int i = size1 - 1, j = size2 - 1; i > 0 && j > 0;) {
		if (str1[i - 1] == str2[j - 1])	i--, j--, str << str1[i - 1];

		else if (lengthTab[i][j] == lengthTab[i - 1][j - 1] + 1)
			str << " SUB(" << str1[i--- 1] << ", " << str2[j--- 1] << ") ";
		else if (lengthTab[i][j] == lengthTab[i - 1][j] + 1) 
			str << " DEL(" << str1[i---1] << ") ";
		else if (lengthTab[i][j] == lengthTab[i][j - 1] + 1) 
			str << " ADD(" << str2[j---1] << ") ";  	
	}
	sub = str.str();

	return lengthTab[size1-1][size2-1];
}

int ED_recursive(const std::string& str1, const std::string& str2) {
	times[1][1] = 0;
	auto result = [str1, str2](int i, int j) {
		auto ED_rec = [str1, str2](int i, int j, auto& ED_ref) mutable {
			times[1][1]++;
			if (i <= 0)	return j;
			if (j <= 0)	return i;

			return(str1[i - 1] == str2[j - 1]) ? ED_ref(i - 1, j - 1, ED_ref) : 1 + std::min(std::min (ED_ref(i, j - 1, ED_ref), ED_ref(i - 1, j, ED_ref)), ED_ref(i - 1, j - 1, ED_ref));
		};

		return ED_rec(i, j, ED_rec);
	};

	return result(str1.size(), str2.size());
}


using namespace std::chrono;

int main() {

	std::pair<std::string, std::string> ED[8] = {
		std::make_pair("INTENTION",  "EXECUTION"),
		std::make_pair("SUNDAY",  "SATURDAY"),
		std::make_pair("CART", "MARCH"),
		std::make_pair("QUARANTINE", "RUNTIME"),
		std::make_pair("DUCK", "BUCK"),
		std::make_pair("BUCKET", "RACKET"),
		std::make_pair("COOK", "BOOK"),
		std::make_pair("SHOOK", "SHAKE")
	};

	int(*functions[])(const std::string&, const std::string&) = {ED_dynamic,ED_recursive};

	std::stringstream EDout, timings;

	auto start = high_resolution_clock::now();
	auto end = high_resolution_clock::now();

	for (int i = 0; i < 8; i++) {
		start = high_resolution_clock::now();
		(*functions[2])(ED[i].first, ED[i].second);
		end = high_resolution_clock::now();
		timings << duration_cast<nanoseconds>(end - start).count();

		timings << "\t";

		start = high_resolution_clock::now();
		(*functions[3])(ED[i].first, ED[i].second);
		end = high_resolution_clock::now();
		timings << duration_cast<nanoseconds>(end - start).count();

		EDout << ED[i].first <<
			"\t" << ED[i].second <<
			"\t" << (*functions[2])(ED[i].first, ED[i].second) <<
			"\t" << sub <<
			"\t" << times[1][0] <<
			"\t" << times[1][1] << "\n";

		timings << "\n";
			
	}
	std::ofstream EDoFile("ED.csv"), timingsoFile("timings.csv");
	EDoFile << EDout.str();
	timingsoFile << timings.str();

	return 0;
}