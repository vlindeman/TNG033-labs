#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iterator>
#include <vector>
#include <iomanip> 


typedef std::map<std::string, int> frequency_table;
typedef std::pair<std::string, int> word_pair;

// Functions 
void readTableFile(frequency_table &T, int &counter);
char toLower(char c);
bool notSpecialChar(char ch); 
bool compare(std::pair<std::string, int> p1, std::pair<std::string, int> p2);

// Special chars, to be removed from strings 
const std::string specialChar = "(.,!?:\"();";

int main(){

	frequency_table table;
	int counter = 0;
	readTableFile(table, counter);
	std::ofstream outFile("output.txt");

	// write to file 
	outFile << "Number of words in the file = " << counter << std::endl;
	outFile << "Number unique  words in the file = " << table.size() << std::endl << std::endl;
	outFile << "\n\nFrequency table sorted alphabetically ...\n\n";
		
	// copy results in alphabetical order to file 
	std::ostream_iterator<word_pair> osit(outFile, "\n");
	std::copy(table.begin(), table.end(), osit);

	// create vector 
	std::vector<word_pair> frequency(table.size());

	// copy from table to vector 
	copy(table.begin(), table.end(), frequency.begin());

	// sort vector by number of 
	std::sort(frequency.begin(), frequency.end(), compare);

	// copy results by decreasing order of words’ frequency to file 
	outFile << "\n\nFrequency table sorted by frequence ...\n\n";
	std::ostream_iterator<word_pair> out_(outFile, "\n");
	std::copy(frequency.begin(), frequency.end(), out_);

	return 0; 
}

// Read file and store in frequency_table
void readTableFile(frequency_table &T, int &counter) {

	std::string in_line = "";
	//std::ifstream istream("uppgift1_kort.txt");
	std::ifstream istream("uppgift1.txt");

	while (istream >> in_line) {
		std::string tableStr = "";

		// all upper case letters transformed to lower case letters 
		std::transform(in_line.begin(), in_line.end(), in_line.begin(), std::tolower); 

		// remove special chars 
		std::copy_if(in_line.begin(), in_line.end(), back_inserter(tableStr), notSpecialChar);

		// add to table and update counter 
		T[tableStr]++;
		counter++;
	}

}

// Converts char to lower case 
char toLower(char c){
	return std::tolower(c);
}

// Returns true if char is not a special char, oterwise false 
bool notSpecialChar(char ch) {
	if (std::find(specialChar.begin(), specialChar.end(), ch) != specialChar.end())
		return false; 
	return true;
}

// operator<<
namespace std {
	ostream& operator<<(ostream& os, const word_pair& WP)	{
		return os << std::setw(15) << left << WP.first << " " << WP.second;
	}
}

// compare int value of the pairs 
bool compare(std::pair<std::string, int> p1, std::pair<std::string, int> p2) {
	return p1.second > p2.second;
}