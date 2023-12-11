#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

// given the coordinates (p) of a symbol and the set digit coordinates(numCoords),
// return whether p is adjacent (including diagonals) to a digit
bool hasDigitNeighbor(pair<int, int>& p, set< pair<int, int> >& numCoords) {
	pair<int, int> n(p.first - 1, p.second);
	bool hasN = numCoords.count(n);
	if (hasN) {
		return true;
	}
	
	pair<int, int> ne(p.first - 1, p.second + 1);
	bool hasNE = numCoords.count(ne);
	if (hasNE) {
		return true;
	}
	
	pair<int, int> e(p.first, p.second + 1);
	bool hasE = numCoords.count(e);
	if (hasE) {
		return true;
	}
	
	pair<int, int> se(p.first + 1, p.second + 1);
	bool hasSE = numCoords.count(se);
	if (hasSE) {
		return true;
	}
	
	pair<int, int> s(p.first + 1, p.second);
	bool hasS = numCoords.count(s);
	if (hasS) {
		return true;
	}
	
	pair<int, int> sw(p.first + 1, p.second - 1);
	bool hasSW = numCoords.count(sw);
	if (hasSW) {
		return true;
	}
	
	pair<int, int> w(p.first, p.second - 1);
	bool hasW = numCoords.count(w);
	if (hasW) {
		return true;
	}
	
	pair<int, int> nw(p.first - 1, p.second - 1);
	bool hasNW = numCoords.count(nw);
	if (hasNW) {
		return true;
	}
	
	// no digit neighbors found
	return false;
}

void readLines(string& fileName) {
	ifstream ifs(fileName);
	if (!ifs) {
		cerr << "Error reading file" << endl;
	}
	
	string line;
	vector<string> grid;
	
	// TODO: rather than scan for symbols and then
	// find adjacent nums; try scanning for nums,
	// then finding any adjacent symbols. If symbol,
	// convert string num to int and add to runningSum
	
	set< pair<int, int> > symCoords;	// coordinates of symbols
	set< pair<int, int> > numCoords;	// coordinates of numbers
	int j = 0;	// row index
	
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
	for (string str : grid) {
		cout << str << endl;
	}
	
//	cout << endl;
//	cout << "symbols:" << endl;
//	for (auto itr = symCoords.begin(); itr != symCoords.end(); ++itr) {
//		pair<int, int> p = *itr;
//		cout << p.first << ", " << p.second << endl;
//	}
//	cout << endl;
//	cout << "numbers:" << endl;
//	if (numCoords.empty()) {
//		cout << "Numbers is empty!" << endl;
//	}
//	for (auto itr = numCoords.begin(); itr != numCoords.end(); ++itr) {
//		pair<int, int> p = *itr;
//		cout << p.first << ", " << p.second << endl;
//	}

	// check each symbol for adj numbers
	cout << "symbols w/ digit neighbors:" << endl;
	for (auto itr = symCoords.begin(); itr != symCoords.end(); ++itr) {
		pair<int, int> p = *itr;
		if (hasDigitNeighbor(p, numCoords)) {
			cout << p.first << ", " << p.second << endl;
			// TODO:
			// - get number string from numCoords
			// - remove visited coords from numCoords
			// - convert number string to int
			// - add to running sum
			// - return running sum
		}
	}
}


int main(int argc, char *argv[]) {
	string fileName = argv[1];
	readLines(fileName);
}