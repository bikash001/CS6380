#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
using namespace std;

void mutation(vector<vector<int> *> &);
void genPath(vector<int> &);
void printPath(vector<int> &);
void crossOver(vector<int> &, vector<int> &);
void selection(vector<vector<int> *> &, vector<vector<double> *> &);
double evaluate(vector<int> &, vector<vector<double> *> &);
double greedy(vector<int> &, vector<vector<double> *> &);
bool sum(std::vector<int> &v);
void free_pops(vector<vector<int>*> &);

#endif