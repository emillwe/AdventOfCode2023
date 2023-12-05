#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

int MAX_RED = 12;
int MAX_GREEN = 13;
int MAX_BLUE = 14;

char ASCII_OFFSET = '0';

int charToDigit(char c) {
	return c - ASCII_OFFSET;
}

int stringToInt(string& indexStr) {
	int numDigits = indexStr.length();
	int result = 0;
	int place = 1;
	for (auto itr = indexStr.rbegin(); itr < indexStr.rend(); ++itr) {
		char digitChar = *itr;
		int digit = charToDigit(digitChar);
		result += (digit * place);
		place *= 10;
	}
	
	return result;
}

void trimLeadingWhitespace(string& str) {
	if (isspace(str[0])) {
		str = str.substr(1, str.length());
	}
}

// for this round,
// update max dice for each color
void processRound(string& line, int *rPtr, int *gPtr, int *bPtr, int *maxPtr) {
	// split draw into colors: deliminate by ','
	istringstream iss2(line);
	string thisDraw;
	
	while(getline(iss2, thisDraw, ',')) {
		trimLeadingWhitespace(thisDraw);
				
		istringstream iss3(thisDraw);
	
		string color;
		string digits;
		
		iss3 >> digits;
		int numCubes = stringToInt(digits);
		
		iss3 >> color;
				
		// check color
		if (color == "red") {
			maxPtr = rPtr;
		}
		else if (color == "green") {
			maxPtr = gPtr;
		} else { // color == "blue"
			maxPtr = bPtr;
		}
		
		*maxPtr = max(numCubes, *maxPtr);
		
		cout << *rPtr << " " << *gPtr << " " << *bPtr << endl;
	}
}

// process whether this game is valid
bool processGame(string& line) {
	// running max of RGB cubes
	int redMax, greenMax, blueMax = 0;
	int *maxPtr;
	
	// split by draw: deliminate by ';'
	istringstream iss(line);
	string drawCubes;
	
	while (getline(iss, drawCubes, ';')) {
		// remove leading whitespace
		trimLeadingWhitespace(drawCubes);
		
		// process this round of the game
		processRound(drawCubes, &redMax, &greenMax, &blueMax, maxPtr);
	}
	
	// end of game. Is it valid?
	if (redMax > MAX_RED) {
		return false;
	}
	else if (greenMax > MAX_GREEN) {
		return false;
	}
	else if (blueMax > MAX_BLUE) {
		return false;
	} else { // all valid
		return true;
	}
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
			
			for (int i = 0; i < 2; ++i) {
				iss >> nextWord;
			}
			
			nextWord.pop_back();	// trim ':'
			
			// get game index
			int gameIndex = stringToInt(nextWord);
			
			cout << "Game " << gameIndex << ": " << endl;
			
			string restOfLine;
			getline(iss, restOfLine);

			cout << processGame(restOfLine) << endl;
			
		}
	}
}

int main(int argc, char *argv[]) {
	readLines(argv[1]);
	return 0;
}