#include <random>
#include <vector>
#include <limits>
#include <iostream>
using namespace std;

double greedy(vector<int> &path, vector<vector<double>*> &table)
{
	double total = 0.0;
	int size = path.size();
	random_device dev;
	uniform_int_distribution<int> dist(0,size-1);
	int current = dist(dev);
	path[0] = current;
	bool filled[size];
	for (bool &x : filled) {
		x = false;
	}
	filled[current] = true;
	int spos = 0;
	double min;
	for (int i=1; i<size; ++i) {
		min = numeric_limits<double>::infinity();
		for (int j=0; j<current; ++j) {
			if (!filled[j]) {
				if ((*table[current])[j] < min) {
					min = (*table[current])[j];
					spos = j;
				}
			}
		}
		for (int j=current+1; j<size; ++j) {
			if (!filled[j]) {
				if ((*table[current])[j] < min) {
					min = (*table[current])[j];
					spos = j;
				}
			}
		}
		path[i] = spos;
		current = spos;
		total += min;
		filled[spos] = true;
	}
	total += (*table[current])[path[0]];
	// cout << "gree " << total << endl;
	return total;
}