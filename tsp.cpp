#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <iterator>
#include "header.hpp"
using namespace std;

void mutation(vector<vector<int> *> &A) {
	random_device gen;
	double prob = 0.0005;
	uniform_real_distribution<double> pp(0,1);
	double rs = pp(gen);
	if (rs <= prob) {
		uniform_int_distribution<int> dist(0,(*A[0]).size()-1);
		int low, high;
		int size = A.size();
		for (int i=0; i<size; ++i) {
			do{
				low = dist(gen);
				high = dist(gen);
			} while (low == high);
			swap((*A[i])[low], (*A[i])[high]);
		}
	}
}

void genPath(vector<int> &A)
{
	random_device gen;
	shuffle(A.begin(),A.end(),gen);
}

void printPath(vector<int> &A)
{
	for (int &x: A) {
		cout << x+1 << " ";
	}
	cout << endl << flush;
}

static bool contains(vector<int>::iterator &begin, vector<int>::iterator &end, int k) {
	while (begin <= end) {
		if (*begin == k) {
			return true;
		}
		++begin;
	}
	return false;
}
static bool contains(vector<int> &v, int low, int high, int k) {
	while (low <= high) {
		if (v[low] == k) {
			return true;
		}
		++low;
	}
	return false;
}

static void copy(vector<int> &A, int low, int high) {
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
	uniform_int_distribution<int> dist(0,size);
	do {
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
	vector<int>::iterator aitr, bitr;
	aitr = A.begin()+high-low;
	bitr = B.begin()+high-low;
	for (int k=0; k <= size; ++k) {
		if (!contains(a,low,high,b[k])) {
			*(++aitr) = b[k];
		}
		if (!contains(b,low,high,a[k])) {
			*(++bitr) = a[k];
		}
	}
}

static int sumTotal(int* arr, int size) {
	int total = 0;
	for (int i=0; i<size; ++i) {
		total += *arr;
		++arr;
	}
	return total;
}

double evaluate(vector<int> &A, vector<vector<double>*> &Table) {
	double total = 0;
	int size = A.size();
	for (int i=1; i<size; ++i) {
		total += (*Table[A[i-1]])[A[i]];
	}
	total += (*Table[A[size-1]])[A[0]];
	return total;
}

static int getIndex(vector<double> &vals, double k) {
	int lt = 0;
	int rt = vals.size()-1;
	int mid;
	while (lt < rt) {
		mid = (lt+rt)/2;
		if (vals[mid] == k) {
			return mid;
		} else if (vals[mid] < k) {
			lt = mid+1;
		} else {
			rt = mid;
		}
	}
	return rt;
}

static void make_pops(vector<vector<int>*> &dest, vector<vector<int>*> &src)
{
	int size = src.size();
	for (int i=0; i<size; ++i)
	{
		dest[i] = new vector<int>(*src[i]);
	}
}


void selection(vector<vector<int> *> &A, vector<vector<double> *> &Table) {
	int size = A.size();
	vector<double> vals(size);
	int max = 0;
	vals[0] = 1 / evaluate(*A[0], Table);
	for (int i=1; i<size; ++i) {
		vals[i] = vals[i-1] + 1 / evaluate(*A[i], Table);
	}
	double total = vals[size-1];
	random_device gen;
	uniform_real_distribution<double> dist(0,total);
	int index = 0;
	vector<vector<int> *> parCopy(size);
	make_pops(parCopy, A);
	for (int i=0; i<size; ++i) {
		index = getIndex(vals, dist(gen));
		*A[i] = *parCopy[index];
	}
	free_pops(parCopy);
}