#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

const int ASCII_OFFSET = '0';		// for ASCII to int conversions

// given the coordinates (p) of a symbol and the set digit coordinates(numCoords),
// return coordinates of all adjacent digits
vector< pair<int, int> > getDigitNeighbors(pair<int, int>& p, set< pair<int, int> >& numCoords) {
	vector< pair<int, int> > result;
	
	pair<int, int> n(p.first - 1, p.second);
	bool hasN = numCoords.count(n);
	if (hasN) {
		result.push_back(n);
	}
	
	pair<int, int> ne(p.first - 1, p.second + 1);
	bool hasNE = numCoords.count(ne);
	if (hasNE) {
		result.push_back(ne);
	}
	
	pair<int, int> e(p.first, p.second + 1);
	bool hasE = numCoords.count(e);
	if (hasE) {
		result.push_back(e);
	}
	
	pair<int, int> se(p.first + 1, p.second + 1);
	bool hasSE = numCoords.count(se);
	if (hasSE) {
		result.push_back(se);
	}
	
	pair<int, int> s(p.first + 1, p.second);
	bool hasS = numCoords.count(s);
	if (hasS) {
		result.push_back(s);
	}
	
	pair<int, int> sw(p.first + 1, p.second - 1);
	bool hasSW = numCoords.count(sw);
	if (hasSW) {
		result.push_back(sw);
	}
	
	pair<int, int> w(p.first, p.second - 1);
	bool hasW = numCoords.count(w);
	if (hasW) {
		result.push_back(w);
	}
	
	pair<int, int> nw(p.first - 1, p.second - 1);
	bool hasNW = numCoords.count(nw);
	if (hasNW) {
		result.push_back(nw);
	}
	
	// return coordinates of all adjacent digits
	return result;
}

// given a coordinate (p) of a digit and the input grid, return the number that includes
// this digit as a string, noting coordinates of visited digits along the way
string getNum(pair<int, int>& p, vector<string>& grid, set< pair<int, int> >& visited) {
	int row = p.first;
	string& str = grid[row];
	int i = p.second;	// location of digit inside line
	string result = "";
	
	// have we processed this coordinate already?
	if (visited.count(p)) {
		return result;
	}
	
	// find leftmost digit in this number
	while(i >= 0 && isdigit(str[i])) {
		--i;
	}
	// past end of number: back up
	++i;
	
	while(isdigit(str[i])) {
		visited.insert({p.first, i});
		result += str[i];
		++i;
	}

	return result;
	
}

// convert string of digits to an int
int strToInt(string& str) {
	if (str.empty()) {
		return 0;
	}
	int result = 0;
	int power = 1;
	for (auto itr = str.rbegin(); itr != str.rend(); ++itr) {
		char c = *itr;
		int i = c - ASCII_OFFSET;
		result += (i * power);
		power *= 10;
	}
	return result;
}

// process input and return result
int readLines(string& fileName) {
	ifstream ifs(fileName);
	if (!ifs) {
		cerr << "Error reading file" << endl;
	}
	
	string line;
	vector<string> grid;
	
	set< pair<int, int> > symCoords;	// coordinates of symbols
	set< pair<int, int> > numCoords;	// coordinates of numbers
	set< pair<int, int> > visited;		// coordinates already scanned for digits
	int j = 0;	// row index
	int result = 0;
	
	// save input lines into grid
	// save symbol and number coordinates
	while (!ifs.eof()) {
		getline(ifs, line);		// read line
		grid.push_back(line);	// add line to grid
		
		// save all symbol and part # coordinates
		for (int i = 0; i < line.length(); ++i) {
			char c = line[i];
			if (!isalnum(c) && c != '.') {
				pair<int, int> p(j, i);
				symCoords.insert(p);
			}
			else if (isdigit(c)) {
				pair<int, int> p(j, i);
				numCoords.insert(p);
			}
		}
		
		++j; // next row
	}
	
	// check each symbol
	for (auto itr = symCoords.begin(); itr != symCoords.end(); ++itr) {
		pair<int, int> p = *itr;
		// get all adjacent digits for this symbol
		vector< pair<int, int> > v = getDigitNeighbors(p, numCoords);
		if (!v.empty()) {
			// check each digit
			for (auto itr = v.begin(); itr != v.end(); ++itr) {
				pair<int, int> p = *itr;
				// get number this digit belongs to
				string numStr = getNum(p, grid, visited);
				// add to result
				result += strToInt(numStr);
			}
		}
	}
	return result;
}


int main(int argc, char *argv[]) {
	string fileName = argv[1];
	cout << readLines(fileName) << endl;
}