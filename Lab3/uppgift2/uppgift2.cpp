#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <set>

typedef std::set<std::string> anagram;
typedef std::map<std::string, anagram> anagramMap;
typedef std::pair<std::string, anagram> anagramPair;

int main() {
	// open instream from file 
	std::ifstream inFile("uppgift2_kort.txt");

	if (!inFile) {
		std::cout << "Error: Can't open file";
		return 0;
	}

	anagramMap am;
	anagramMap::iterator it;
	std::string str = "";
	int counter = 0;

	// read from file 
	while (inFile >> str) {
		std::transform(str.begin(), str.end(), str.begin(), tolower);
		std::string anagramWord = str;
		sort(anagramWord.begin(), anagramWord.end());
		am[anagramWord].insert(str);
		counter++;
	}

	std::cout << "Number of words = " << counter << "\n\n--- ANAGRAMS ---\n";

	// create vector with anagram pairs
	std::set<anagramPair> vec(std::begin(am), std::end(am));

	// cout with outstream iterator 
	std::ostream_iterator<anagramPair> osi(std::cout);
	copy(vec.begin(), vec.end(), osi);

	return 0;
}

// operator<< 
namespace std {
	template <typename T>
	ostream& operator<<(ostream& os, std::set<T> S) {

		for (auto it = std::begin(S); it != std::end(S); ++it) {
			os << *it;
		}
		return os;
	}
}

namespace std {
	ostream& operator<<(ostream& os, anagramPair AP) {
		ostream_iterator<string> oit(os, " ");
		if (AP.second.size() > 1) {
			os << AP.second;
			os << " --> " << AP.second.size() << " words." << endl;
		}
		return os;
	}
}
