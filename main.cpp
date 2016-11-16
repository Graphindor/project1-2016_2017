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

typedef vector<nodo> grafo;

// Le sposteremo
void DFS(grafo& GRAFO, int u, vector<int>& ordineVisita, vector<vector<int>>& listaCicli, vector<bool>& visited)
{
	GRAFO[u].visited = true;
	visited[u] = true;
	for(int k:GRAFO[u].neighbor)
	{
		// cout << "=U: " << u << " K: " << k << endl;
		if(!GRAFO[k].visited && !(GRAFO[k].neighbor.empty()))
		{
			ordineVisita.push_back(k);
			for(int i:ordineVisita)
				cout << i << " ";

			cout << endl;

			DFS(GRAFO, k, ordineVisita, listaCicli, visited);
			ordineVisita.pop_back();
			GRAFO[k].visited = false;
		}
		else
		{
			if(k != ordineVisita[ordineVisita.size() - 2])
			{
				// cout << "LOOP?" << endl;
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

	vector<bool> visited(GRAFO.size());

	for(size_t i = 0; i < GRAFO.size(); i++)
	{
		if(!visited[i])
		{
			ordineVisita.push_back(i);
			DFS(GRAFO, i, ordineVisita, listaCicli, visited);
		}
	}

	// ordineVisita.push_back(0);
	// DFS(GRAFO, 0, ordineVisita, listaCicli, visited);

	return listaCicli;
}

int main()
{
	string path = "input/input";
	int N;
	cout << "Input N: ";
	cin >> N;
	path += to_string(N) + ".txt";

	ifstream in(path);

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

	ofstream out("output.txt");
	out << mcd << endl;
	out.close();

	return 0;
}
