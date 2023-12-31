#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const int ASCII_OFFSET = '0';		// string <-> int conversion

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

// given a heat time and charge time, return
// total distance traveled
unsigned long chargeToDist(unsigned long& heatTime, unsigned long& chargeTime) {
	unsigned long runTime = heatTime - chargeTime; // time remaining in heat after charge
	if (runTime < 0) {
		return -1;
	}
	return chargeTime * runTime;
}

// one race: time limit and distance record
struct heat {
	unsigned long time;
	unsigned long distance;
	
	heat(unsigned long& t, unsigned long& d) {
		time = t;
		distance = d;
	}
	
	void print() {
		cout << "Time: " << time << endl;
		cout << "Distance: " << distance << endl;
	}
};

int processHeats(heat& thisHeat, bool print = false) {	
	// get all charge times greater than
	// target distance and mult with result
	int numWins = 0;	// number of winning chargeTimes
	
	// check all possible charge times
	if (print) {
		cout << "Heat: " << endl;
		cout << "time: " << thisHeat.time << " dist: " << thisHeat.distance << endl;
	}
	
	for (unsigned long chargeTime = 1; chargeTime < thisHeat.time; ++chargeTime) {
		// get distance travelled for this charge time
		unsigned long thisDist = chargeToDist(thisHeat.time, chargeTime);
		
		if (print) {
			cout << "charge: " << chargeTime << " dist: " << thisDist << endl;
		}
		
		// found a winning charge time?
		if (thisDist > thisHeat.distance) {
			if (print) {
				cout << "winner!" << endl;
			}
			++numWins;
			if (print) {
				cout << "# of wins: " << numWins << endl;
			}
		}
	}
	
	return numWins;
}

// parse input, return solution
int readLines(string fileName) {
	ifstream ifs(fileName);
	string line;
	
	// read TIME value
	getline(ifs, line);
	istringstream iss(line);
	string time;
	iss >> time;	// read "Time:"
	string fullTime = "";
	while (iss >> time) {
		fullTime += time;
	}
	
	// read DISTANCE values
	getline(ifs, line);
	istringstream is2(line);
	string distance;
	is2 >> distance;	// read "Distance:"
	string fullDistance = "";
	while (is2 >> distance) {
		fullDistance += distance;
	}
	
	unsigned long t = stringToInt(fullTime);
	unsigned long d = stringToInt(fullDistance);
	
	heat thisHeat(t, d);
		
	return processHeats(thisHeat, false);
}

int main(int argc, char* argv[]) {
	cout << readLines(argv[1]) << endl;
	return 0;
}