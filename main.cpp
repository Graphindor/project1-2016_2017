#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct nodo {
	vector<int> neighbor;
	bool visited = false;
};

typedef vector<nodo> grafo;

// Le sposteremo
void DFS(grafo& GRAFO, int u, vector<int>& ordineVisita, vector<vector<int>>& listaCicli)
{
	cout << ordineVisita.size() << " @ ";
	for(int i:ordineVisita)
		cout << i << " ";

	cout << endl;
	GRAFO[u].visited = true;
	for(int k:GRAFO[u].neighbor)
	{
		if(!GRAFO[k].visited && (GRAFO[k].neighbor.size() < 1))
		{
			ordineVisita.push_back(k);
			DFS(GRAFO, k, ordineVisita, listaCicli);
		}
		else
		{
			if(k != ordineVisita[ordineVisita.size() - 1])
			{
				unsigned int pos = find(ordineVisita.begin(), ordineVisita.end(), k) - ordineVisita.begin();
				vector<int> toPush(ordineVisita.begin() + pos, ordineVisita.end());
				for(int i:toPush)
					cout << i << " ";
				cout << endl;
				listaCicli.push_back(toPush);
			}
		}
	}
}

vector<vector<int>> getCycles(grafo GRAFO)
{
	vector<vector<int>> listaCicli;
	vector<int> ordineVisita;

	ordineVisita.push_back(0);
	DFS(GRAFO, 0, ordineVisita, listaCicli);

	return listaCicli;
}

int main()
{
	ifstream in("input3.txt");

	int M, L;
	in >> M >> L;

	grafo GRAFO(M);

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
			cout << j << " ";

		cout << endl;
	}

	vector<vector<int>> listaCicli = getCycles(GRAFO);

	cout << "=== CHECK CICLI ===" << endl;
	cout << "size(): " << listaCicli.size();

	for(vector<int> v:listaCicli)
	{
		for(int i:v)
			cout << i << " ";

		cout << endl;
	}

	return 0;
}
