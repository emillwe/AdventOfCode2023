#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int ASCII_OFFSET = '0';	// char <--> int conversions

// print contents of a map to std::cout
void printMap(map<int, int>& m) {
	for (auto itr = m.begin(); itr != m.end(); ++itr) {
		pair<int, int> p = *itr;
		cout << p.first << ": " << p.second << endl;
	}
	cout << endl;
}

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

// given a map and string of values, initialize map
void initMap(map<int, int>& m, string str) {
	istringstream iss(str);
	string buf1, buf2, buf3;

	iss >> buf1;
	iss >> buf2;
	iss >> buf3;
	
	int dStart = stringToInt(buf1);		// destination start
	int sStart = stringToInt(buf2);		// source start
	int rangeLen = stringToInt(buf3);	// range length
	
	for (int i = 0; i < rangeLen; ++i) {
		m[sStart] = dStart;
		++sStart;
		++dStart;
	}
}

// read and process lines of input
int readLines(string fileName) {
	// open file
	ifstream ifs(fileName);
	
	if(!ifs) {
		cerr << "Error reading file!" << endl;
		return -1;
	}
	
	string buf;		// buffer
	
	// read "seeds:"
	ifs >> buf;
	
	// save line of seeds
	string seedStr;
	getline(ifs, seedStr);
	
	// save each seed
	istringstream iss(seedStr);
	vector<string> seeds;
	string thisSeed;
	while (iss >> thisSeed) {
		seeds.push_back(thisSeed);
	}
	
	// buf == "seeds:"
	getline(ifs, buf);
	getline(ifs, buf);
	
	// conversion maps
	map<int, int> seedToSoil;
	map<int, int> soilToFert;
	map<int, int> fertToWater;
	map<int, int> waterToLight;
	map<int, int> lightToTemp;
	map<int, int> tempToHumid;
	map<int, int> humidToLoc;
	
	vector< map<int, int> > maps = {
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
	
	// fencepost: find "seed-to-soil map"
	while(!mapNames.count(buf)) {
		getline(ifs, buf);
	}
//	getline(ifs, buf);
	
	// init all maps
	for (int i = 0; i < maps.size(); ++i) {
		// read until next map name
		while(!mapNames.count(buf)) {
			getline(ifs, buf);
		}
		
		// read until next empty line; init map
		while(!buf.empty() && !ifs.eof()) {
			getline(ifs, buf);
			initMap(maps[i], buf);
		}
		
		// test map
		cout << "Map " << i + 1 << endl;
		printMap(maps[i]);
	}
	
	// find the lowest location number that corresponds to any of the initial seeds
	int minLoc = INT_MAX;
	int input;
	for (int i = 0; i < seeds.size(); ++i) {
		input = stringToInt(seeds[i]);
		cout << "Seed: " << input << endl;
		
		// convert through each medium in maps
		for (int j = 0; j < maps.size(); ++j) {
			map<int, int>* thisMap = &(maps[j]);
			
			// translate if this value has a conversion
			int count = thisMap->count(input);
			if (thisMap->count(input)) {
				input = (*thisMap)[input];
			} // otherwise, input value stays the same
			
			cout << "next: " << input << endl;
			
		}
		cout << "\n";
		// done converting: input is location
		
		// track min location
		if (input < minLoc) {
			cout << "New min: " << input << endl;
			cout << endl;
			minLoc = input;
		}
	}	
	
	return minLoc;	
}




int main(int argc, char* argv[]) {
	cout << readLines(argv[1]) << endl;
	return 0;
}