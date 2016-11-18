#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>

using namespace std;

struct nodo {
	vector<int> neighbor;
	bool visited = false;
};

typedef vector<nodo> grafo_t;

typedef vector<vector<int>> species_t;

// Le sposteremo
void DFS(grafo_t& GRAFO, int u, vector<int>& ordineVisita, vector<vector<int>>& listaCicli)
{
	GRAFO[u].visited = true;
	for(int k:GRAFO[u].neighbor)
	{
		if(!GRAFO[k].visited && !(GRAFO[k].neighbor.empty()))
		{
			ordineVisita.push_back(k);
			DFS(GRAFO, k, ordineVisita, listaCicli);
			ordineVisita.pop_back();
		}
		else
		{
			if(k != ordineVisita[ordineVisita.size() - 2])
			{
				unsigned int pos = find(ordineVisita.begin(), ordineVisita.end(), k) - ordineVisita.begin();
				vector<int> toPush(ordineVisita.begin() + pos, ordineVisita.end());

				if(!toPush.empty())
					listaCicli.push_back(toPush);
			}
		}
	}
}

vector<vector<int>> getCycles(grafo_t& GRAFO)
{
	vector<vector<int>> listaCicli;
	vector<int> ordineVisita;

	for(size_t i = 0; i < GRAFO.size(); i++)
		if(!GRAFO[i].visited)
		{
			ordineVisita.push_back(i);
			DFS(GRAFO, i, ordineVisita, listaCicli);
		}

	return listaCicli;
}

int MCD(unsigned int x, unsigned int y)
{
	while(y != 0)
	{
		unsigned int z = x % y;
		x = y;
		y = z;
	}

	return x;
}

int main()
{

	ifstream in("input.txt");

	int M, L;
	in >> M >> L;

	grafo_t GRAFO(M);
	species_t species(M);
	vector<pair<int, int>> edges;


	for(int i = 0; i < M; i++)
		species[i].resize(M);

	for(int i = 0; i < L; i++)
	{
		int src, dest;
		in >> src >> dest;

		pair<int, int> edge(src, dest);

		edges.push_back(edge);
		GRAFO[src].neighbor.push_back(dest);
		GRAFO[dest].neighbor.push_back(src);
	}

	cout << endl << "=== CHECK GRAFO ===" << endl;
	for(unsigned int i = 0; i < GRAFO.size(); i++)
	{
		cout << i << ": ";
		for(int j:GRAFO[i].neighbor)
			cout << "[" << j << ", " << species[i][j] << "]";

		cout << endl;
	}

	cout << endl << "=== FIND CYCLES===" << endl;
	vector<vector<int>> cycleList = getCycles(GRAFO);

	int x = 1;
	for(vector<int> v:cycleList)
	{
		cout << "[" << x++ << "] ";
		for(int i:v)
			cout << i << " ";

		cout << endl;
	}

	// unsigned int mcd = cycleList[0].size();
	// unsigned int min = M;

	// for(vector<int> v:cycleList)
	// {
	// 	if(min > v.size())
	// 		min = v.size();
	//
	// 	int x = mcd;
	// 	int y = v.size();
	//
	// 	// Il MCD e` calcolato usando l'algoritmo Euclideo
	// 	while (y > 0) {
	// 		int r = x % y;
	// 		x = y;
	// 		y = r;
	// 	}
	//
	// 	mcd = x;
	// }

	unsigned int mcd = cycleList[0].size();
	for(unsigned int i = 0; i < cycleList.size() - 1; i++)
	{
		unsigned int _mcd = mcd;
		mcd = MCD(cycleList[i].size(), cycleList[i + 1].size());
		mcd = MCD(mcd, _mcd);

		unsigned int common_arch = 0;
		for(int z:cycleList[i])
		{
			for(int j:cycleList[i + 1])
			{
				if(z == j)
					common_arch++;
			}
		}
		common_arch = (common_arch > 0) ? common_arch - 1 : 0;

		cout << common_arch << endl;

		mcd = MCD(mcd, cycleList[i].size() + cycleList[i + 1].size() - common_arch);
	}

	cout << "MCD: " << mcd << endl;
	vector<int> MCDS;
	for(unsigned int i = 1; i <= (mcd / 2); i++)
		if((mcd % i) == 0)
			MCDS.push_back(i);

	MCDS.push_back(mcd);
	reverse(MCDS.begin(), MCDS.end());

	cout << "MCDS: ";
	for(int m:MCDS)
		cout << m << " ";
	cout << endl;

	for(vector<int> cycle:cycleList)
	{
		int current = 0;
		cycle.push_back(cycle[0]);
		for(unsigned int i = 0; i < cycle.size() - 1; i++)
		{

			current %= mcd;

			int n1, n2;
			n1 = cycle[i];
			n2 = cycle[i + 1];

			int* sp1 = &(species[n1][n2]);
			int* sp2 = &(species[n2][n1]);

			*sp1 = current + 1;
			*sp2 = current + 1;
			current++;
		}
	}

	cout << endl << "=== CHECK SPECIES ===" << endl;

	ofstream out("output.txt");

	out << mcd << endl;
	for(pair<int, int> edge:edges)
	{
		int spec = species[edge.first][edge.second] - 1;
		cout << edge.first << ", " << edge.second << " - " << spec << endl;
		out << ((spec < 0) ? 0 : spec) << endl;
	}

	out.close();

	return 0;
}
