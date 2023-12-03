#include <iostream>
#include <fstream>

using namespace std;

// isolate digits from line
string getCalibStr(string line) {
	string result = "";
	for (int i = 0; i < line.length(); ++i) {
		char c = line[i];
		if (isdigit(c)) {
			result += c;
		}
	}
	
	return result;
}

// get first and last digits
string getFirstLast(string nums) {
	string result = "";
	char first = *(nums.begin());
	char last = *(nums.rbegin());
	result += first;
	result += last;
	return result;
}

// convert 2-digit strings to integers
int strToInt(string str) {
	char ASCII_OFFSET = '0';
	char c1 = *(str.begin());
	char c2 = *(str.rbegin());
	int tens = 10 * (c1 - ASCII_OFFSET);
	int ones = c2 - ASCII_OFFSET;
	return tens + ones;
}

// 
int readLines(string fileName) {
	ifstream input(fileName);	// input file
	
	if (!input) {
		cout << "Error reading file" << endl;
	}
	
	int runningSum = 0;		// sum of calibrations
	string next;		// next line
	
	// read until nothing left in stream
	while(getline(input, next)) {
		if (!next.empty()) {
			string nums = getCalibStr(next);			// get digits only
			string twoDigits = getFirstLast(nums);		// get outside digits
			int thisCalib = strToInt(twoDigits);		// convert to int
			runningSum += thisCalib;					// add to running sum
		}
	}
	
	return runningSum;
}

int main(int argc, char *argv[]) {
	cout << readLines(argv[1]) << endl;
	
	return 0;
}