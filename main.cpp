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
	cout << "size(): " << listaCicli.size() << endl;

	vector<vector<int>> listaCicli = getCycles(GRAFO);

	cout << "=== CHECK CICLI ===" << endl;
	cout << "size(): " << listaCicli.size() << endl;

	int mcd = listaCicli[0].size();
	int min = M;

	for(vector<int> v:listaCicli)
	{
					cout << "il ciclo è lungo: " << v.size() << endl;

					if (min > v.size()) {
									min=v.size();
					}

					int x = mcd;
					int y = v.size();

					// Il MCD e` calcolato usando l'algoritmo Euclideo
					while (y > 0) {
									int r = x % y;
									x = y;
									y = r;
					}

					mcd = x;

					for(int i:v) {
									cout << i << " ";
					}
					cout << endl;
	}

	cout << "l'mcd: " << mcd << endl;
	cout << "il ciclo più lungo: " << min << endl;

	return 0;
}
