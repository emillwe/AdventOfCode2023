#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <pair>

using namespace std;

void readLines(string& fileName) {
	ifstream ifs(fileName);
	if (!ifs) {
		cerr << "Error reading file" << endl;
	}
	
	string line;
	
	set<pair<int, int>> coords;
	
	while (!ifs.eof()) {
		getline(ifs, line);
		cout << line << endl;
		
		
	}
}



int main(int argc, char *argv[]) {
	string fileName = argv[1];
	readLines(fileName);
}