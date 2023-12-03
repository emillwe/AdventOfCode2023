#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

int stringToIndex(string& indexStr) {
	char ASCII_OFFSET = '0';
	int numDigits = indexStr.length();
	int result = 0;
	int place = 1;
	for (int i = 0; i < numDigits; ++i) {
		char digitChar = indexStr[i];
		int digit = digitChar - ASCII_OFFSET;
		result += (digit * place);
		place *= 10;
	}
	
	return result;
}

void readLines(string fileName) {
	ifstream input(fileName);	// input file
	
	if(!input) {
		cout << "Error reading file" << endl;
	}
	
	int runningSum = 0;		// running sum of game indexes
	string nextLine;			// next line in stream
	
	// read until nothing left in stream
	while(getline(input, nextLine)) {
		if (!nextLine.empty()) {
			istringstream iss(nextLine);	// read words from line
			string nextWord;
			getline(iss, nextWord, ' ');	// read "Game"
			getline(iss, nextWord, ' ');	// read "<Game index>:"
			nextWord.pop_back();			// "<Game Index>"
			
			// get game index
			int gameIndex = stringToIndex(nextWord);
			
		}
	}
}

int main(int argc, char *argv[]) {
	readLines(argv[1]);
	return 0;
}