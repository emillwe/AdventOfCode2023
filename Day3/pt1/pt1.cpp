#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

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
	
	set<pair<int, int>> coords;	// coordinates of symbols
	int j = 0;	// row index
	while (!ifs.eof()) {
		getline(ifs, line);		// read line
		grid.push_back(line);	// add line to grid
		
		// save all symbol coordinates
		for (int i = 0; i < line.length(); ++i) {
			char c = line[i];
			if (!isalnum(c) && c != '.') {
				pair<int, int> p(j, i);
				coords.insert(p);
			}
		}
		
		++j; // next row
	}
	for (string str : grid) {
		cout << str << endl;
	}
	
	cout << endl;
	for (auto itr = coords.begin(); itr != coords.end(); ++itr) {
		pair<int, int> p = *itr;
		cout << p.first << ", " << p.second << endl;
	}
}


int main(int argc, char *argv[]) {
	string fileName = argv[1];
	readLines(fileName);
}