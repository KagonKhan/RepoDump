#include <iostream>
#include <regex>
#include <vector>

void printMatches(std::string str, const std::regex& reg) {
	std::smatch matches;

	std::cout << std::boolalpha;

	while (std::regex_search(str, matches, reg)) {
		std::cout << "Is there a match: " << matches.ready() << '\n';

		std::cout << "Are there no matches: " << matches.empty() << '\n';
		
		std::cout << "Number of matches: " << matches.size() << '\n';


		std::cout << "Match: " << matches.str(1) << '\n'; // output first match
		str = matches.suffix().str();
		std::cout << '\n';



	}

}


void printMatches2(std::string str, std::regex reg) {

	std::cout << '\n' << str << "\n\t";

	std::sregex_iterator currentMatch(str.begin(), str.end(), reg);

	std::sregex_iterator lastMatch;

	while (currentMatch != lastMatch) {
		std::smatch match = *currentMatch;
		std::cout << match.str() << ", ";
		currentMatch++;
	}
	std::cout << '\n';
}

int main() {

	std::vector<std::string> str;
	std::vector<std::regex> reg;

	str.push_back("The ape was at the apex");
	str.push_back("I picked the pickle");
	str.push_back("Cat rat mat fat pat");
	str.push_back("Cat rat mat fat pat");
	str.push_back("Cat rat mat fat pat");
	str.push_back("F.B.I. I.R.S. CIA");
	str.push_back("12345");
	str.push_back("123 12345 123456 1234567");
	str.push_back("412-767-5309");
	str.push_back("Random Name");
	str.push_back("a as ape bug");
	str.push_back("valid.email@gmail.com notvalid.com val@com.pl");
	

	
	reg.push_back(std::regex("(ape[^ ]?)"				)); // Match anything with ape in front and everything without a space after, ? - is not required
	reg.push_back(std::regex("(pick([^ ]+)?)"			)); // Match anything with pick in front and everything without a space after, + - one or more, ? - is not required
	reg.push_back(std::regex("([crmfp]at)"				)); // Match anything with any of these letters in front and everything witho at after
	reg.push_back(std::regex("([C-Fc-f]at)"				)); // Match anything with any of these letters in front and everything witho at after
	reg.push_back(std::regex("([^Cr]at)"				)); // Match none of these letters in front and everything witho at after
	reg.push_back(std::regex("([^ ]\..\..\.)"			)); // Match no space in front, dot, any char, dot, any char, dot
	reg.push_back(std::regex("(\\d)"					));	// Match numbers, one by one
	reg.push_back(std::regex("(\\d{5,7})"				));	// Match numbers, one by one, having 5-7 length
	reg.push_back(std::regex("(\\w{3}-\\w{3}-\\w{4})"	));	// Match numbers, one by one, having 5-7 length
	reg.push_back(std::regex("(\\w{2,20}\\s\\w{2,20})"	));	// Match word space word, length 2-20
	reg.push_back(std::regex("(a[a-z]*)"				));	// Match word beginnig a, having any small letter, 1 or more 
	reg.push_back(std::regex("[\\w._%+-]{1,20}@[\\w.-]{2,20}\\.[A-za-z]{2,3}"));	// Match email

	// \d - [0-9],	\w = [a-zA-Z0-9]
	// \D - [^0-9]	\W = [^a-zA-Z0-9]
	// White spaces: \b, \f, \r, \t, \v, \s[\f\n\r\t\v], \S[^\f\n\r\t\v]
	// ? - zero or 1 preceding token
	// + - 1 or more preceding token
	// * - 0 or more preceding token

	std::string owlFood = std::regex_replace(str[3], reg[3], "Owl");
	std::cout << owlFood << '\n';

	std::string multiline ="This is a\n multiline string\nthat has many lines";
	std::regex findNewLine("\n");
	std::regex word("[ ]a");
	std::string noMultiline = std::regex_replace(multiline, findNewLine, " ");
	noMultiline = std::regex_replace(noMultiline, word, " not a");
	std::cout << noMultiline << '\n';



	for (int i = 0; i < str.size(); ++i) {
		printMatches2(str[i], reg[i]);
	}

		
			




}