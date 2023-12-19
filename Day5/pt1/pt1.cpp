#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int ASCII_OFFSET = '0';	// char <--> int conversions

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
void readLines(string fileName) {
	// open file
	ifstream ifs(fileName);
	
	if(!ifs) {
		cerr << "Error reading file!" << endl;
		return;
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
	
	// fencepost: find 
	while(!mapNames.count(buf)) {
		getline(ifs, buf);
		cout << buf << endl;
	}

//	// init all maps
//	for (int i = 0; i < maps.size(); ++i) {
//		// read until map title
//		while(!mapNames.count(buf) && !buf.empty()) {
//			getline(ifs, buf);
//			cout << buf << endl;
//		}
//	}
	

//	// save seed to soil conversions
//	while (!buf.empty()) {	
//		getline(ifs, buf);
////		cout << buf << endl;
//		initMap(seedToSoil, buf);
//	}
//	
//	// save soil to fertilizer conversions
//	while (!buf.empty()) {	
//		getline(ifs, buf);
////		cout << buf << endl;
//		initMap(seedToSoil, buf);
//	}
	
	return;	
}




int main(int argc, char* argv[]) {
	readLines(argv[1]);
	return 0;
}