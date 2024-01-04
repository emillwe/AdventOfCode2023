#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

const int ASCII_OFFSET = '0';

const map<char, int> cardOrder {
	{'2', 2},
	{'3', 3},
	{'4', 4},
	{'5', 5},
	{'6', 6},
	{'7', 7},
	{'8', 8},
	{'9', 9},
	{'T', 10},
	{'J', 11},
	{'Q', 12},
	{'K', 13},
	{'A', 14}
};

// convert string num to int
int stringToInt(string& str) {
	int result = 0;
	int mult = 1;
	
	for (auto itr = str.rbegin(); itr != str.rend(); ++itr) {
		char c = *itr;
		int digit = c - ASCII_OFFSET;
		result += (digit * mult);
		mult *= 10;
	}
	
	return result;
}


// given a string of cards, return its value (1-7)
int getValue(string& cards) {
	map<char, int> cardFreqs;	// histogram of cardss
	map<int, int> duplicates;	// occurences of pairs, triples, four-of-a-kind, etc. 
	
	// build histogram
	for (char c : cards) {
		++cardFreqs[c];
	}
	
	// track pairs, triples, four-of-a-kind, etc.
	for (auto p : cardFreqs) {
		int freq = p.second;
		++duplicates[freq];
	}
	
	int value = 0;
	// 5 of a kind: 7 points
	if (duplicates[5]) {
		value = 7;
	}
	// four of a kind: 6 points
	else if (duplicates[4]) {
		value = 6;
	}
	// full house: 5 points
	else if (duplicates[3] && duplicates[2]) {
		value = 5;
	}
	// three of a kind: 4 points
	else if (duplicates[3]) {
		value = 4;
	}
	// two pairs: 3 points
	else if (duplicates[2] == 2) {
		value = 3;
	}
	// one pair: 2 points
	else if (duplicates[2]) {
		value = 2;
	} else {	// high card: 1 point
		value = 1;
	}
	
	return value;
}

// model a hand of cards, with wager and relative value (1-7)
struct hand {
	string cards;	// cards in this hand
	int bid;		// this hand's bet
	int value;		// this hand's score, 1-7
	
	hand(string& thisHand, string& thisBid) {
		cards = thisHand;
		bid = stringToInt(thisBid);
		value = getValue(cards);
	}
	
	void print() {
		cout << cards << " " << bid << " value: " << value;
	}
};

void testValues() {
	vector<string> hands {
		"32T3K",
		"T55J5",
		"KK677",
		"KTJJT",
		"QQQJA",
	};
	
	for (string hand : hands) {
		cout << "Hand: " << hand << " Value: " << getValue(hand) << endl;
	}
}

void testHands(vector<hand>& hands) {
	for (hand h : hands) {
		h.print();
		cout << endl;
	}
}

// given an input file stream ifs and a vector of hands,
// initialize all hands
void initHands(ifstream& ifs, vector<hand>& hands) {
	string buffer;
	while(getline(ifs, buffer)) {
		istringstream iss(buffer);
		string thisHand, thisBid;
		iss >> thisHand;
		iss >> thisBid;
		hand h(thisHand, thisBid);
		hands.push_back(h);
	}
}


int main(int argc, char* argv[]) {
	string fileName;
	if (argc) {
		fileName = argv[1];
	}
	
	ifstream ifs(fileName);
	if (!ifs || fileName.empty()) {
		cerr << "Error reading file: " << fileName << endl;
		return -1;
	}
	
	// all hands/bids in this game
	vector<hand> hands;
	
	// parse input and initialize all hands/bids
	initHands(ifs, hands);
	
	// sort hands according to hand value
	sort(hands.begin(), hands.end(),
		[](hand& a, hand&b) {
			return a.value < b.value;
		}
	);
		
	// TODO: sort hands of same value by high card (in card order a la war)	
	
	
		
	return 0;
}