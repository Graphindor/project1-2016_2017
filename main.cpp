#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

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

	ifstream in("input/input0.txt");

	int M, L;
	in >> M >> L;

	grafo_t GRAFO(M);
	species_t species(M);
	for(int i = 0; i < M; i++)
		species[i].resize(M);

	for(int i = 0; i < L; i++)
	{
		int src, dest;
		in >> src >> dest;

		GRAFO[src].neighbor.push_back(dest);
		GRAFO[dest].neighbor.push_back(src);
	}

	cout << "=== CHECK GRAFO ===" << endl;
	for(unsigned int i = 0; i < GRAFO.size(); i++)
	{
		cout << i << ": ";
		for(int j:GRAFO[i].neighbor)
			cout << "[" << j << ", " << species[i][j] << "]";

		cout << endl;
	}

	cout << endl << "=== CHECK SPECIES ===" << endl;
	for(vector<int> y:species)
	{
		for(int x:y)
			cout << x << " ";

		cout << endl;
	}

	cout << endl << "=== FIND CYCLES===" << endl;
	vector<vector<int>> cycleList = getCycles(GRAFO);

	for(vector<int> v:cycleList)
	{
		for(int i:v)
			cout << i << " ";

		cout << endl;
	}

	cout << endl << "=== CHECK SPECIES POST ===" << endl;
	for(vector<int> y:species)
	{
		for(int x:y)
			cout << x << " ";

		cout << endl;
	}

	return 0;
}
