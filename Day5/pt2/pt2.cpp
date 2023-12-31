#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <tuple>

using namespace std;

const int ASCII_OFFSET = '0';	// char <--> int conversions

// convert string num to int
unsigned long stringToInt(string& str) {
	unsigned long result = 0;
	unsigned long mult = 1;
	
	for (auto itr = str.rbegin(); itr != str.rend(); ++itr) {
		char c = *itr;
		int digit = c - ASCII_OFFSET;
		result += (digit * mult);
		mult *= 10;
	}
	
	return result;
}

// model range of seeds
struct seedRange {
	unsigned long start;
	unsigned long range;
};

// model collection of seed ranges
struct seedGroup {
	vector<seedRange> seedRanges;
	
	// track min and max seed values in group
	unsigned long minSeed = 0;
	unsigned long maxSeed = INT_MAX;
	
	// initialize a seed group from a vector comprising strings
	// <seedStart1>, <seedRange1>, <seedStart2>, . . . <seedRangeN>
	void init(vector<string>& seeds) {
		for (int i = 0; i < seeds.size(); i += 2) {
			seedRange sRange;
			sRange.start = stringToInt(seeds[i]);
			sRange.range = stringToInt(seeds[i+1]);
			
			seedRanges.push_back(sRange);
			
			// update limits
			minSeed = min(minSeed, sRange.start);
			maxSeed = max(maxSeed, sRange.start + sRange.range - 1);
		}
	}
	
	// check if a given seed falls within this seed group
	bool isGoodSeed(unsigned long& thisSeed) {
		for (auto s : seedRanges) {
			// is this seed within bounds of this range?
			bool inRange = (
				thisSeed >= s.start &&
				thisSeed < (s.start + s.range)
			);
			if (!inRange) {
				continue;
			} else {
				return inRange;
			}
		}
		return false;
	}
};

// model conversions between media
struct conversion {
	// lists of map specs (destination, source, range)
	// Each element is a specifies a conversion range
	vector< tuple<unsigned long, unsigned long, unsigned long> > data;
	
	// given a line (str) of seed specs, read into data
	// as a single range
	void init(string& str) {
		istringstream iss(str);
		string next;
		vector<unsigned long> values;
		
		// convert all strings to ints
		while(iss >> next) {
			values.push_back(stringToInt(next));
		}
		
		// save values in this conversion range
		data.push_back(make_tuple(values[0], values[1], values[2]));
	}
	
	// convert input value through this medium, testing each range
	// unmapped inputs are unchanged
	unsigned long processInput(unsigned long input) {
		for (auto itr = data.begin(); itr != data.end(); ++itr) {
			auto t = *itr;
			unsigned long dStart = get<0>(t);
			unsigned long sStart = get<1>(t);
			unsigned long range = get<2>(t);
			
			// is this the right range for input?
			if (input < dStart) {
				continue;
			}
			
			unsigned long offset = input - dStart;
			unsigned long output = sStart + offset;
			
			// is output in range?
			if (output >= sStart + range) {
				continue;
			} else { // input is in this range
				return output;
			}
		}
		
		// range not found: input maps to itself
		return input;
	}
	
	// TODO: expand for all intermediate values ?
	void print() {
		for (auto itr = data.begin(); itr != data.end(); ++itr) {
			auto t = *itr;
			
			unsigned long dStart = get<0>(t);
			unsigned long sStart = get<1>(t);
			unsigned long range = get<2>(t);
			
			cout << dStart << " " << sStart << " " << range << endl;
		}
	}
};

// given this conversion, test  if this input matches this target
bool testConv(conversion& conv, long input, long target) {
	return conv.processInput(input) == target;
}

// parse input, return solution
unsigned long readLines(string fileName) {
	// open file
	ifstream ifs(fileName);
	
	if(!ifs) {
		cerr << "Error reading file!" << endl;
		return -1;
	}
	
	string buf;		// buffer
	
	// read "seeds:"
	ifs >> buf;
	
	// save line of seed ranges
	string seedStr;
	getline(ifs, seedStr);
	
	// save each seed range
	istringstream iss(seedStr);
	vector<string> seeds;
	string thisSeed;
	while (iss >> thisSeed) {
		seeds.push_back(thisSeed);
	}
	
	// init seed group
	seedGroup sg;
	sg.init(seeds);
	
//	cout << "Seed ranges: " << endl;
//	for (auto itr = seeds.begin(); itr != seeds.end(); itr += 2) {
//		cout << *itr << ", " << *(itr + 1) <<endl;
//	}
	
	// conversion maps
	conversion seedToSoil;
	conversion soilToFert;
	conversion fertToWater;
	conversion waterToLight;
	conversion lightToTemp;
	conversion tempToHumid;
	conversion humidToLoc;
	
	vector<conversion> maps = {
		seedToSoil,
		soilToFert,
		fertToWater,
		waterToLight,
		lightToTemp,
		tempToHumid,
		humidToLoc
	};
	
	set<string> mapNames = {
		"seed-to-soil map:",
		"soil-to-fertilizer map:",
		"fertilizer-to-water map:",
		"water-to-light map:",
		"light-to-temperature map:",
		"temperature-to-humidity map:",
		"humidity-to-location map:"
	};
	
	// init all maps
	for (int i = 0; i < maps.size(); ++i) {
		while(!mapNames.count(buf) && !ifs.eof()) {
			getline(ifs, buf);
		} // buf now contains a map name
		
		while(!buf.empty() && !ifs.eof()) {
			getline(ifs, buf);
			if (!buf.empty()) {
				// initialize this map
				maps[i].init(buf);
			}
		}
	}
	
	// find the lowest location number that corresponds to any of the initial seeds
	unsigned long minLoc = INT_MAX;
	unsigned long input;
	unsigned long i;
	
	// test all possible location values
	for (i = 0; i < INT_MAX; ++i) {
		// convert through each medium in maps (backwards)
		input = i;
//		cout << "input: " << input << endl;
		
		// test this seed
		for (auto itr = maps.rbegin(); itr != maps.rend(); ++itr) {
			conversion thisConv = *itr;
			input = thisConv.processInput(input);
//			cout << "next: " << input << endl;
		}
		// done converting: input is a seed
		
		// check if result is a valid seed
//		for (unsigned long j = 0; j < seeds.size(); j += 2) {
//			unsigned long seedStart = stringToInt(seeds[j]);
//			unsigned long seedRange = stringToInt(seeds[j+1]);
//			
//			if (input >= seedStart && input < (seedStart + seedRange)) {
//				return i;
//			}
//		}
		
		// can we skip this seed?
		if (input < sg.minSeed || input > sg.maxSeed) {
			continue;
		}
		
		// need to check seed
		if (sg.isGoodSeed(input)) {
			return i;
		}
	}
	return -1;
}

void test() {
	conversion conv;
	
	string input = "0 15 37";
	string input2 = "37 52 2";
	string input3 = "39 0 15";
	
	conv.init(input);
	conv.init(input2);
	conv.init(input3);
	conv.print();
	cout << endl;
	
	bool pass1 = testConv(conv, 81, 81);
	bool pass2 = testConv(conv, 14, 53);
	bool pass3 = testConv(conv, 57, 57);
	bool pass4 = testConv(conv, 13, 52);
	
	if(pass4) {
		cout << "success!" << endl;
	} else {
		cout << "Failure!" << endl;
	}
}

int main(int argc, char* argv[]) {
	cout << "Min location: " << readLines(argv[1]) << endl;
	return 0;
}
