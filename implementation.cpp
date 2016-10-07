#include "header.hpp"
#include <random>
#include <algorithm>
#include <climits>
#include <queue>

struct prObj{
	int index;
	double val;
};

struct LessThan{
	bool operator()(const prObj &lhs, prObj &rhs) const {
		return lhs.val < rhs.val;
	}  
};

struct GreaterThan{
	bool operator()(const prObj &lhs, prObj &rhs) const {
		return lhs.val > rhs.val;
	}  
};

bool lessThan(const prObj &lhs, const prObj &rhs)
{
	return lhs.val < rhs.val;
}
bool greaterThan(const prObj &lhs, const prObj &rhs)
{
	return lhs.val > rhs.val;
}

int g_min = INT_MAX;

void sum(std::vector<int> v) {
	int total = 0;
	int size = v.size();
	int arr[size];
	for (int &x : arr) {
		x = 0;
	}
	for (int i=0; i<size; ++i) {
		total += v[i];
		arr[v[i]] = 1;
	}
	if (total != 4950) {
		cout << "error "<< total << " size " << size << endl;
		for (int i=0; i < size ; ++i) {
			if (arr[i] == 0) 
				cout << i+1 << " ";
		}
		cout << endl;
	} else {
		// cout << "success" << endl;
	}
	// cout << total << endl;
}

void geneticAlgo(vector<vector<double>> &Table){
	/*
		First randomly generate a sufficiently large population of tours.
		Then call "selection" on this population to select tours for reproduction.
		Then randomly split these into pairs and call crossOver for each pair.
		Collect population of children. Print best if better than the previous best.
	*/
	int n = Table.size();

	vector<vector<int>> population;
	int population_size = 200;
	int parent_retain = 50;
	int i,j;
	int k = 1, count = 0;
	for(i=0;i<population_size;i++){
		vector<int> v(n);
		greedy(v,Table);
		population.push_back(v);
	}
	// cout << "---------------------------------------" << endl;
	int csize = population_size/2;
	vector<struct prObj> par(n);
	vector<struct prObj> child(n);
	random_device gen;
	while(true)
	{
		selection(population, Table);
		// for (int i=0; i<population.size(); ++i) {
		// 	cout << evaluate(population[i], Table) << endl;
		// }
		vector<vector<int>> tempPop(population);
		shuffle(population.begin(), population.end(), gen);
		for(i=0; i<csize; i++){
			crossOver(population[i], population[population_size - i - 1]);
		}
		int max_index;
		double val1, val2, min;
		min = numeric_limits<double>::infinity();

		for(i=0;i<population_size;i++){
			val1 = evaluate(population[i], Table);
			child[i].index = i;
			child[i].val = val1;
			val2 = evaluate(tempPop[i], Table);
			par[i].index = i;
			par[i].val = val2;
			if (val1 > val2) {
				val1 = val2;
			}
			if(val1 < g_min){
				g_min = val1;
				max_index = i;
				cout << val1 << endl;
				// printPath(population[i]);
			}
		}
		sort(par.begin(), par.end(), lessThan);
		// for (int i=1; i<par.size(); ++i) {
		// 	if (par[i-1].val > par[i].val) {
		// 		cout << "error one" << endl;
		// 	}
		// }
		sort(child.begin(), child.end(), greaterThan);
		// for (int i=1; i<child.size(); ++i) {
		// 	if (child[i-1].val < child[i].val) {
		// 		cout << "error two" << endl;
		// 	}
		// }
		for (int i=0; i<parent_retain; ++i) {
			population[child[i].index] = tempPop[par[i].index];
		}
		// count++;
	}
	// cout << "final " << g_min << endl;
}

void readInput(char* filename, vector<vector<double>>& Table){
	FILE *fp;
	fp = fopen(filename, "r");
	char waste[100];
	fscanf(fp, "%s", waste);
	int n, i = 0, j = 0;
	fscanf(fp, "%d", &n);
	while(i<2*n)
	{
		fscanf(fp, "%s", waste);
		i++;
	}

	i = 0;
	
	double f;
	while(i<n)
	{
		vector<double> v;
		j=0;
		while(j<n)
		{
			fscanf(fp, "%lf", &f);	
			v.push_back(f);
			j++;
		}
		Table.push_back(v);
		i++;
	}
	fclose(fp);
}

void printTable(vector<vector<double>>& Table){
	int size = Table.size();
	int i, j;
	for(j=0;j<size;j++)
	{
		for(i=0;i<size;i++){
			cout << Table[j][i] << " ";
		}	
		cout << endl;
	}
	
	cout << endl << flush;
}

int main(int argc, char* argv[]){

	if(argc<2)
	{
		return -1;
	}

	vector<vector<double>> Table;
	readInput(argv[1], Table);
	// vector<int> b(100);
	// double temp;
	// double min = numeric_limits<double>::infinity();
	// for (int i=0; i<100; ++i) {
	// 	temp = greedy(b, Table);
	// 	if (temp < min) {
	// 		min = temp;
	// 	}
	// }
	// cout << min << endl;
	geneticAlgo(Table);
}