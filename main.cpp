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

bool contains(vector<int> target, vector<vector<int>> source)
{
	for(vector<int> v:source)
	{
		if(target == v)
			return true;
	}

	return false;
}

// Le sposteremo
void DFS(grafo_t& GRAFO, int u, vector<int>& ordineVisita, vector<vector<int>>& listaCicli, vector<bool>& visited)
{
	GRAFO[u].visited = true;
	visited[u] = true;
	for(int k:GRAFO[u].neighbor)
	{
		if(!GRAFO[k].visited && !(GRAFO[k].neighbor.empty()))
		{
			ordineVisita.push_back(k);
			DFS(GRAFO, k, ordineVisita, listaCicli, visited);
			ordineVisita.pop_back();
			GRAFO[k].visited = false;
		}
		else
		{
			if(k != ordineVisita[ordineVisita.size() - 2])
			{
				unsigned int pos = find(ordineVisita.begin(), ordineVisita.end(), k) - ordineVisita.begin();
				vector<int> toPush(ordineVisita.begin() + pos, ordineVisita.end());

				if(!toPush.empty())
				{
					vector<int> rev(toPush.begin(), toPush.end());
					reverse(rev.begin() + 1, rev.end());
					if(!contains(toPush, listaCicli) && !contains(rev, listaCicli))
						listaCicli.push_back(toPush);
				}
			}
		}
	}
}

vector<vector<int>> getCycles(grafo_t& GRAFO)
{
	vector<vector<int>> listaCicli;
	vector<int> ordineVisita;

	vector<bool> visited(GRAFO.size());

	for(size_t i = 0; i < GRAFO.size(); i++)
	{
		if(!visited[i])
		{
			ordineVisita.push_back(i);
			DFS(GRAFO, i, ordineVisita, listaCicli, visited);
		}
	}

	return listaCicli;
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

	unsigned int mcd = cycleList[0].size();
	unsigned int min = M;

	for(vector<int> v:cycleList)
	{
		if(min > v.size())
			min = v.size();

		int x = mcd;
		int y = v.size();

		// Il MCD e` calcolato usando l'algoritmo Euclideo
		while (y > 0) {
			int r = x % y;
			x = y;
			y = r;
		}

		mcd = x;
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
