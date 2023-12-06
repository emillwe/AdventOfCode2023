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

// read thorugh input, process lines, get solution
int readLines(string fileName) {
	ifstream input(fileName);	// input file
	
	if(!input) {
		cout << "Error reading file" << endl;
	}
	
	int runningSum = 0;		// running sum of game indexes
	string nextLine;		// next line in stream
	
	// read until nothing left in stream
	while(getline(input, nextLine)) {
		if (!nextLine.empty()) {
			istringstream iss(nextLine);	// read words from line
			string nextWord;
			
			// read "Game: <Game index>:"
			for (int i = 0; i < 2; ++i) {
				iss >> nextWord;
			}
			
			nextWord.pop_back();	// trim ':' from game index
			
			// get game index digits
			int gameIndex = stringToInt(nextWord);
						
			string restOfLine;
			getline(iss, restOfLine);
			
			// running max of RGB cubes
			int redMax = 0, greenMax = 0, blueMax = 0;
			int *maxPtr;
			
			// split by round: deliminate by ';'
			istringstream iss2(restOfLine);
			string drawCubes;
			while (getline(iss2, drawCubes, ';')) {
				// remove leading whitespace
				trimLeadingWhitespace(drawCubes);
				
				// split draw into colors: deliminate by ','
				istringstream iss3(drawCubes);
				string thisDraw;
				while(getline(iss3, thisDraw, ',')) {
					trimLeadingWhitespace(thisDraw);
							
					istringstream iss3(thisDraw);
				
					string color;
					string digits;
					
					iss3 >> digits;
					int numCubes = stringToInt(digits);
					
					iss3 >> color;
							
					// check color
					if (color == "red") {
						maxPtr = &redMax;
					}
					else if (color == "green") {
						maxPtr = &greenMax;
					} else { // color == "blue"
						maxPtr = &blueMax;
					}
					
					// update that color's max
					*maxPtr = max(numCubes, *maxPtr);
				}
			}
			
			// end of game
			
			// check maxima
			/*
			cout << "R: " << redMax << endl;
			cout << "G: " << greenMax << endl;
			cout << "B: " << blueMax << endl;
			*/
			
			int power = redMax * greenMax * blueMax;
			runningSum += power;
		}
	}
	return runningSum;
}

int main(int argc, char *argv[]) {
	cout << readLines(argv[1]) << endl;
	return 0;
}