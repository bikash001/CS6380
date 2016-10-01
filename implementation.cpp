#include "header.hpp"
#include <random>
#include <algorithm>

void geneticAlgo(vector<vector<double>> &Table){
	/*
		First randomly generate a sufficiently large population of tours.
		Then call "selection" on this population to select tours for reproduction.
		Then randomly split these into pairs and call crossOver for each pair.
		Collect population of children. Print best if better than the previous best.
	*/
	int n = Table.size();
	vector<vector<int>> population;
	int population_size = 10;
	int i,j;
	int k = 10, count = 0;
	while(count < k)
	{
		for(i=0;i<population_size;i++){
			vector<int> v;
			for(j=0;j<n;j++){
				v.push_back(j);	
			}
			genPath(v);
			population.push_back(v);
		}

		selection(population, Table);

		random_device gen;
		shuffle(population.begin(), population.end(), gen);
		int cc = 0;
		for(i=0;i<population_size/2;i++){
			crossOver(population[i], population[population_size - i - 1]);
		}


		int max = 0;
		int max_index, val;
		for(i=0;i<population_size;i++){
			val = evaluate(population[i], Table);
			if(val>max){
				max = val;
				max_index = i;
			}
		}
		// printPath(population[max_index]);
		cout << max << endl;
		count++;
	}
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
	geneticAlgo(Table);
}