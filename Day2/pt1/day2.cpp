#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

int MAX_RED = 12;
int MAX_GREEN = 13;
int MAX_BLUE = 14;

int stringToIndex(string& indexStr) {
	char ASCII_OFFSET = '0';
	int numDigits = indexStr.length();
	int result = 0;
	int place = 1;
	for (auto itr = indexStr.rbegin(); itr < indexStr.rend(); ++itr) {
		char digitChar = *itr;
		int digit = digitChar - ASCII_OFFSET;
		result += (digit * place);
		place *= 10;
	}
	
	return result;
}

// process whether this number of cubes is valid
bool processCubes(string& nextOfLine) {
	// running max of RGB cubes
	
	// split by draw: deliminate by ';'
	// -> string draw
	
	// split draw into colors: deliminate by ','
	// -> string colors
	
	// pointer to int for max
	// switch color to decide which max to point to
	// check max
	
	// end of line: for each color, if max > spec max, return false
	// (outside loop) return true
	
	return false;
}

// read thorugh input, process lines, get solution
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
			
			string restOfLine;
			getline(iss, restOfLine);

			cout << processCubes(nextOfLine) << endl;
			
		}
	}
}

int main(int argc, char *argv[]) {
	readLines(argv[1]);
	return 0;
}