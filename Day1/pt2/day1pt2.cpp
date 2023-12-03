#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// constant for ascii <-> int
char ASCII_OFFSET = '0';

// digit first letters -> digit strings
map<char, vector<string>> charToOptions {
	{'z', {"zero"}},
	{'o', {"one"}},
	{'t', {"two", "three"}},
	{'f', {"four", "five"}},
	{'s', {"six", "seven"}},
	{'e', {"eight"}},
	{'n', {"nine"}}
};

// digit last letters -> reversed digit strings
map<char, vector<string>> charToOptionsRev {
	{'e', {"eno", "eerht", "evif", "enin"}},
	{'o', {"orez", "owt"}},
	{'r', {"ruof"}},
	{'x', {"xis"}},
	{'n', {"neves"}},
	{'t', {"thgie"}}
};

// digit strings -> digit chars
map<string, int> stringToInt {
	{"zero", 0},
	{"one", 1},
	{"two", 2},
	{"three", 3},
	{"four", 4},
	{"five", 5},
	{"six", 6},
	{"seven", 7},
	{"eight", 8},
	{"nine", 9}
};

// get tens digit char from line
int getTensPlace(string line) {
	for (int i = 0; i < line.length(); ++i) {
		if (isdigit(line[i])) {
			// found digit: done
			return line[i] - ASCII_OFFSET;
		}
		else if (charToOptions.find(line[i]) == charToOptions.end()) {
			// no digits start with this char
			continue;
		} else {
			// get all possible digit strings to follow this char
			vector<string> options = charToOptions[line[i]];
			
			// test them all
			for (string option : options) {
				int len = option.length();
				string test = line.substr(i, len);
				if (test == option) {
					return stringToInt[test];
				}
			}
		}
	}
	
	// didn't find digit
	return -1;
}

// get ones digit char from line
int getOnesPlace(string line) {
	// search backwards
	reverse(line.begin(), line.end());
		
	for (int i = 0; i < line.length(); ++i) {
		// cout << "Testing: " << line[i] << endl;
		if (isdigit(line[i])) {
			// found digit: done
			return line[i] - ASCII_OFFSET;
		}
		else if (charToOptionsRev.find(line[i]) == charToOptionsRev.end()) {
			// no digits end with this char
			continue;
		} else {
			// get all possible digit strings to follow this char
			vector<string> options = charToOptionsRev[line[i]];
			
			// test them all
			for (string option : options) {
				int len = option.length();
				string test = line.substr(i, len);
				if (test == option) {
					reverse(test.begin(), test.end());
					return stringToInt[test];
				}
			}
		}
	}
	
	// didn't find digit
	return -1;
}

// process all lines of input
int readLines(string fileName) {
	ifstream input(fileName);	// input file
	
	if (!input) {
		cout << "Error reading file" << endl;
	}
	
	int runningSum = 0;		// sum of calibrations
	string next;			// next line
	
	// read until nothing left in stream
	while(getline(input, next)) {
		if (!next.empty()) {
			int tens = getTensPlace(next);	// get tens digit
			int ones = getOnesPlace(next);	// get ones digit
			int thisCalib = (tens * 10) + ones;
			runningSum += thisCalib;	// add to running sum
		}
	}
	
	return runningSum;
}

int main(int argc, char *argv[]) {
	cout << readLines(argv[1]) << endl;
	
	return 0;
}