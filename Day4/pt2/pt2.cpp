#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_set>

using namespace std;

void trimWhitespace(string& str) {
	while (isspace(str.front()) && !str.empty()) {
		str = str.substr(1, str.length());
	}
	while (isspace(str.back()) && !str.empty()) {
		str = str.substr(0, str.length() - 1);
	}
}

// given a vector of target cards and a set of my cards,
// return the number of matches common to the two
int processRound(vector<string>& targets, unordered_set<string>& myCards) {
	int score = 0;
	
	// search for each target
	for (auto itr = targets.begin(); itr != targets.end(); ++itr) {
		string thisCard = *itr;
		if (myCards.count(thisCard)) {	// a match!
			++score;
		}
	}
	
	return score;
}

// process input and return score
int readLines(string& fileName) {
	ifstream ifs(fileName);
	if (!ifs) {
		cerr << "Error reading file" << endl;
		return -1;
	}
	
	int totalCopies = 0;	// total number of cards
	int curLine = 1;		// line index
	
	map<int, int> numCopies({ {1, 0} });
	
	string line;
	
	while(!ifs.eof()) {
		getline(ifs, line);
		istringstream iss(line);
		string temp;
		
		cout << "ROUND: " << curLine << endl;
		
		// read "Card <n>:"
		for (int i = 0; i < 2; ++i) {
			iss >> temp;
		}
		
		// save cards to match (targets)
		string card1;
		getline(iss, card1, '|');
		istringstream cardStream(card1);
		vector<string> targetCards;
		string cardVal;
		while(cardStream >> cardVal) {
			targetCards.push_back(cardVal);
		}
		
		// save my cards
		string card2;
		getline(iss, card2, '|');
		istringstream cardStream2(card2);
		unordered_set<string> myCards;
		string cardVal2;
		while(cardStream2 >> cardVal2) {
			myCards.insert(cardVal2);
		}
		
		// process score for this round
		int numMatches = processRound(targetCards, myCards);
		
		// each line has at least one copy
		++numCopies[curLine];
		
		// update copy counts for the next <numMatches> lines
		for (int i = 1; i <= numMatches; ++i) {
			numCopies[curLine + i] += numCopies[curLine];
		}
		
		// add all copies of this card to total
		totalCopies += numCopies[curLine];
				
		++curLine;
	}
	
	return totalCopies;
}


int main(int argc, char *argv[]) {
	string fileName = argv[1];
	cout << readLines(fileName) << endl;
	return 0;
}