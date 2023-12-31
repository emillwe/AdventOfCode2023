#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const int ASCII_OFFSET = '0';		// string <-> int conversion
const int NUM_CATEGORIES = 2;		// e.g. "TIME and DISTANCE"

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
int chargeToDist(int& heatTime, int& chargeTime) {
	int runTime = heatTime - chargeTime; // time remaining in heat after charge
	if (runTime < 0) {
		return -1;
	}
	return chargeTime * runTime;
}

// one race: time limit and distance record
struct heat {
	int time;
	int distance;
	
	heat(int& t, int& d) {
		time = t;
		distance = d;
	}
	
	void print() {
		cout << "Time: " << time << endl;
		cout << "Distance: " << distance << endl;
	}
};

int processHeats(vector<heat>& heats, bool print = false) {
	int result = 1;		// running product
	
	// for each heat, get all charge times greater than
	// target distance and mult with result
	for (auto heat : heats) {
		int numWins = 0;	// number of winning chargeTimes
		
		// check all possible charge times
		if (print) {
			cout << "Heat: " << endl;
			cout << "time: " << heat.time << " dist: " << heat.distance << endl;
		}
		
		for (int chargeTime = 1; chargeTime < heat.time; ++chargeTime) {
			// get distance travelled for this charge time
			int thisDist = chargeToDist(heat.time, chargeTime);
			
			if (print) {
				cout << "charge: " << chargeTime << " dist: " << thisDist << endl;
			}
			
			// found a winning charge time?
			if (thisDist > heat.distance) {
				if (print) {
					cout << "winner!" << endl;
				}
				++numWins;
				if (print) {
					cout << "# of wins: " << numWins << endl;
				}
			}
		}
		
		result *= numWins;
		if (print) {
			cout << "result: " << result << endl;
		}
	}
	
	return result;
}

// parse input, return solution
int readLines(string fileName) {
	ifstream ifs(fileName);
	string line;
	
	vector<heat> heats;		// series of races
	vector<int> times;		// heat time limits
	vector<int> distances;	// heat maximum distance
	
	// read TIME values
	getline(ifs, line);
	istringstream iss(line);
	string time;
	iss >> time;	// read "Time:"
	while (iss >> time) {
		times.push_back(stringToInt(time));	// save time for this heat
	}
	
	// read DISTANCE values
	getline(ifs, line);
	istringstream is2(line);
	string distance;
	is2 >> distance;	// read "Distance:"
	while (is2 >> distance) {
		distances.push_back(stringToInt(distance));	// save time for this heat
	}
	
	// save heat data
	for (int i = 0; i < times.size(); ++i) {
//		cout << "Heat: " << i + 1 << endl;
		heat thisHeat(times[i], distances[i]);
		heats.push_back(thisHeat);
//		thisHeat.print();
//		cout << endl;
	}
		
	return processHeats(heats, false);
}

int main(int argc, char* argv[]) {
//	cout << readLines(argv[1]) << endl;
	cout << readLines(argv[1]) << endl;
	return 0;
}