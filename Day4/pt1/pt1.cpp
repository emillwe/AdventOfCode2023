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
// return the score of this round
int processRound(vector<string> targets, unordered_set<string> myCards) {
	int score = 0;
	
	// search for each target
	for (auto itr = targets.begin(); itr != targets.end(); ++itr) {
		string thisCard = *itr;
		if (myCards.count(thisCard)) {	// a match!
			// first match is worth one point
			if (score == 0) {
				score++;
			} else {	// otherwise, score doubles
				score *= 2;
			}
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
	
	int totalScore = 0;
	
	string line;
	
	while(!ifs.eof()) {
		getline(ifs, line);
		istringstream iss(line);
		string temp;
		
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
		int roundScore = processRound(targetCards, myCards);
		
		// add to total
		totalScore += roundScore;
	}
	
	return totalScore;
}


int main(int argc, char *argv[]) {
	string fileName = argv[1];
	cout << readLines(fileName) << endl;
	return 0;
}