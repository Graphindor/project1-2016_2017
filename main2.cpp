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

	for(size_t i = 0; i < GRAFO.size(); i++)
	{
		if(!GRAFO[i].visited)
		{
			ordineVisita.push_back(i);
			DFS(GRAFO, i, ordineVisita, listaCicli);
		}
	}

	return listaCicli;
}

bool cleanList(int k,grafo GRAFO, vector<int> L1,vector<int> L2){
	int counter =0;
	bool res=false;
	for(int i=0;i<GRAFO[k].neighbor.size();i++){

		for(int j=0;j<L1.size();i++)
			for(int t=0;t<L2.size();t++){
				if( (GRAFO[k].neighbor[i]==L1[j]) && (GRAFO[k].neighbor[i]==L2[t]) ){
					counter+=1;
					if(counter>=2){
						res=true; 
					}
					else{cout << "Non ci sono vicini uguali" << endl;}
				}
			}

	
	}
	return res;
}
vector<vector<int>> newCycles(vector<vector<int>> & cycleList,grafo & GRAFO){


	vector<vector<int>> newCycles2;
	
	for(int i=0;i<cycleList.size();i++){
	
		for(int j=i+1;j<cycleList.size();j++)
		{
				//controllo se hanno elementi in comune
				vector<int> commonItems;
				commonItems.resize(cycleList[i].size());
				vector<int> tmp;
			for(int k=0;k<cycleList[i].size();k++)
			{

				for(int t=0;t<cycleList[j].size();t++)
				{

						if(!(cycleList[i][k]==cycleList[j][t]&&(cleanList(cycleList[i][k],GRAFO,cycleList[i],cycleList[j])))){

							//commonItems.push_back(cycleList[i][k]);
							//clean commonItems
							tmp.push_back(cycleList[i][k]);

						
							}
				}
			}
				newCycles2.push_back(tmp);

				
				

		}


	}






return newCycles2;

}

int main()
{
	ifstream in("input.txt");

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
	vector<vector<int>> newCicli = newCycles(listaCicli,GRAFO);

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
