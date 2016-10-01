#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

void genPath(vector<int> &A)
{
	random_device gen;
	shuffle(A.begin(),A.end(),gen);
}

void printPath(vector<int> &A)
{
	for (int &x: A) {
		cout << x << " ";
	}
	cout << endl;
}

bool contains(vector<int>::iterator begin, vector<int>::iterator end, int k) {
	while (begin <= end) {
		if (*begin == k) {
			return true;
		}
		++begin;
	}
	return false;
}

void copy(vector<int>::iterator &dst, vector<int>::iterator &src, vector<int>::iterator end) {
	while (src <= end) {
		*dst = *src;
		++dst;
		++src;
	}
}

void copy(vector<int> &A, int low, int high) {
	std::vector<int>::iterator dst = A.begin();
	while (low <= high) {
		*dst = A[low];
		++dst;
		++low;
	}
}

void crossOver(vector<int> &A, vector<int> &B)
{
	random_device gen;
	int low, high;
	int size = A.size() - 1;
	do {
		uniform_int_distribution<int> dist(0,size);
		low = dist(gen);
		high = dist(gen);
		while (low == high) {
		high = dist(gen);
		}
		if (low > high) {
			swap(low, high);
		}
	} while (low == 0 && high == size);
	vector<int> a(A);
	vector<int> b(B);
	copy(A, low, high);
	copy(B, low, high);
	vector<int>::iterator aitr, bitr, abegin, bbegin, aend, bend;
	abegin = a.begin()+low;
	aend = a.begin() + high;
	bbegin = b.begin() + low;
	bend = b.begin() + high;
	aitr = A.begin()+low;
	bitr = B.begin()+low;
	for (int k=0; k < low; ++k) {
		if (!contains(abegin, aend, b[k])) {
			*(++aitr) = b[k];
		}
		if (!contains(bbegin, bend, a[k])) {
			*(++bitr) = a[k];
		}
	}
	for (int k=high+1; k < size; ++k) {
		if (!contains(abegin, aend, b[k])) {
			*(++aitr) = b[k];
		}
		if (!contains(bbegin, bend, a[k])) {
			*(++bitr) = a[k];
		}
	}
}

double evaluate(vector<int> &A, vector<vector<double>> &Table) {
	double total = 0;
	int size = A.size();
	for (int i=1; i<size; ++i) {
		total += Table[A[i-1]][A[i]];
	}
	total += Table[A[size-1]][0];
	return total;
}

void selection(vector<vector<int>> &A, vector<vector<double>> &Table) {
	int size = A.size();
	double vals[size];
	for (int i=0; i<size; ++i) {
		vals[i] = evaluate(A[i], Table);
	}
	double max = max_element(vals, vals+size);
}

int main()
{
	vector<int> foo {1,2,3,4,5};
	genPath(foo);
	printPath(foo);
}