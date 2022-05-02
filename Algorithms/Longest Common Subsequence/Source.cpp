#include <vector>
#include <iostream>
#include <string>
#include <functional>
#include <sstream>
#include <chrono>
#include <fstream>

int times[2][2];

std::string sub = "";

int LCS_dynamic(const std::string &str1, const std::string &str2) {
	times[0][0] = 0;
	sub = "";

	int size1 = str1.length() + 1, size2 = str2.length() + 1;
	std::vector<std::vector<int>> lengthTab(size1, std::vector<int>(size2, 0));
	std::string substring = "";

	auto result = [&str1, &str2, &substring, &lengthTab](int size1, int size2) {
		for (int i = 1; i < size1; i++)
			for (int j = 1; j < size2; j++)
			times[0][0]++, lengthTab[i][j] = (str1[i - 1] == str2[j - 1]) ? lengthTab[i - 1][j - 1] + 1 : std::max(lengthTab[i - 1][j], lengthTab[i][j - 1]);

		for (int i = size1 - 1, j = size2 - 1; i > 0 && j > 0;)
			(str1[i - 1] == str2[j - 1]) ? substring += str1[i-- - 1], j-- : (lengthTab[i - 1][j] > lengthTab[i][j - 1]) ? i-- : j--;
		std::reverse(substring.begin(), substring.end());
	};

	result(size1, size2);
	sub = substring;
	return lengthTab[size1-1][size2-1];
}

int LCS_recursive(const std::string& str1, const std::string& str2) {
	times[0][1] = 0;
	auto result = [str1, str2](int i, int j) {
		auto LCS_rec = [str1, str2](int i, int j, auto& LCS_ref) {
			times[0][1]++;
			if (str1[i] == '\0' || str2[j] == '\0')
				return 0;
			else return (str1[i] == str2[j])? 1 + LCS_ref(i + 1, j + 1, LCS_ref) : std::max(LCS_ref(i + 1, j, LCS_ref), LCS_ref(i, j + 1, LCS_ref));
		};
		
		return LCS_rec(i, j, LCS_rec);
	};
	
	return result(0, 0);
}


using namespace std::chrono;

int main() {
	std::pair<std::string, std::string> LCS[8] = {
		std::make_pair("ABCDGH",  "AEDFHR"),
		std::make_pair("AGGTAB",  "GXTXAYB"),
		std::make_pair("ABCBDAB", "BDCABA"),
		std::make_pair("XMJYAUZ", "MZJAWXU"),
		std::make_pair("AFSAFAA", "AFA"),
		std::make_pair("123123123123", "111"),
		std::make_pair("123123123", "1212"),
		std::make_pair("25", "235234")
	};


	int(*functions[])(const std::string&, const std::string&) = {LCS_dynamic, LCS_recursive};

	std::stringstream LCSout, timings;

	auto start = high_resolution_clock::now();
	auto end = high_resolution_clock::now();

	for (int i = 0; i < 8; i++) {

		start = high_resolution_clock::now();
		(*functions[1])(LCS[i].first, LCS[i].second);
		end = high_resolution_clock::now();
		timings << duration_cast<nanoseconds>(end - start).count();

		timings << "\t";

		start = high_resolution_clock::now();
		(*functions[0])(LCS[i].first, LCS[i].second);
		end = high_resolution_clock::now();
		timings << duration_cast<nanoseconds>(end - start).count();


		LCSout << LCS[i].first <<
			"\t" << LCS[i].second <<
			"\t" << (*functions[0])(LCS[i].first, LCS[i].second) <<
			"\t" << sub <<
			"\t" << times[0][0] <<
			"\t" << times[0][1] << "\n";		

		timings << "\n";
	}



	std::ofstream LCSoFile("LCS.csv"), timingsoFile("timings.csv");
	LCSoFile << LCSout.str();
	timingsoFile << timings.str();

	return 0;
}