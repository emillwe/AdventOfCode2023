#include <vector>


struct DigitTrie {
	char letter;
	bool isRoot;
	bool isEnd;
	vector<DigitTrie> next;
	string digitWord = "";
}

DigitTrie zeroZ;
zeroZ.letter = 'z';
zeroZ.isRoot = true;
zeroZ.isEnd = false;

DigitTrie zeroE;
zeroE.letter = 'e';
zeroE.isRoot = false;
zeroE.isEnd = false;

DigitTrie zeroR;
zeroR.letter = 'r';
zeroR.isRoot = false;
zeroR.isEnd = false;

DigitTrie zeroO;
zeroO.letter = 'o';
zeroO.isRoot = false;
zeroO.isEnd = true;
zeroO.digitWord = "zero";

// there must be a better way!