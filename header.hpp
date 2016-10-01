#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
using namespace std;

void genPath(vector<int> &A);
void printPath(vector<int> &A);
void crossOver(vector<int> &A, vector<int> &B);
void selection(vector<vector<int> > &A, vector<vector<double> > &Table);
int evaluate(vector<int> &A, vector<vector<double>> &Table);

#endif