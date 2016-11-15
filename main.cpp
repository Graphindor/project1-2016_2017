#include <iostream>
#include <vector>
#include <string>
#include <list>

#include <limits> // for numeric_limits

#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
#include <new>
#include <fstream>
using namespace std;

typedef int vertex_t;
struct neighbor {
    vertex_t target;
    neighbor(vertex_t arg_target)
        : target(arg_target) { }
};
typedef vector<vector<neighbor> > adjacency_list_t;
/*
void AddToAdjacencyList(adjacency_list_t &adjacency_list, vector<pair<pair<int,int>,int> > &v, int index)
{
    bool found = false;

    for(int i = 0; i < adjacency_list[v[index].first.first].size() && found == false; i++)
        if(adjacency_list[v[index].first.first][i].target == v[index].first.second)
            found = true;

    if(found == false)
        adjacency_list[v[index].first.first].push_back(neighbor(v[index].first.second,v[index].second));
}
void dfs(int x, adjacency_list_t &ls)
{
    state[x] = 1;
    cout << "x==>> " << x << endl;
    cout << "I'm visiting " << x << " with size => " << ls[x].size() << endl;
    if(ls[x].size() > 0)
    for(int j = 0; j < ls[x].size(); j++)
    {
        cout << "ls[" << x << "][" << j << "].target => " << ls[x][j].target << endl;
        cout << "parent[" << x << "].target => " << parent[x].target << endl;
        if(state[ls[x][j].target] == 1 && parent[x].target != ls[x][j].target)
        {
            cout << "Closed cycle since state[ls["<< x <<"]["<<j<<"].target] => " << state[ls[x][j].target] << endl;
            parent[ls[x][j].target].target = x;
            theNodeInTheCycle = ls[x][j].target; //ls[x][j] belongs to the cycle since state[ls[x][j]]==1
            t = 0;
        }
        if(state[ls[x][j].target] == 0)// && parent[x].target != -1)
        {
            parent[ls[x][j].target].target = x;
            dfs(ls[x][j].target, ls);
        }
    }
}

vector <neighbor> GetCycle ()
{
    vector <neighbor> cycle;
    int firstNodeInTheCycle = theNodeInTheCycle;
    do
    {
            theNodeInTheCycle = parent[theNodeInTheCycle].target;
            theWeightInTheCycle = parent[theNodeInTheCycle].weight;
            cycle.push_back (neighbor(theNodeInTheCycle,theWeightInTheCycle));
            cout << "theNodeInTheCycle => " << theNodeInTheCycle << " firstNodeInTheCycle => " << firstNodeInTheCycle << endl;
    } while (theNodeInTheCycle != firstNodeInTheCycle && theNodeInTheCycle != -1);

    reverse(cycle.begin(), cycle.end()); //to get them in the right order
    if(theNodeInTheCycle == -1)
        cycle.clear();

    return cycle;
}
*/



int main(){

	ifstream in("input.txt");

    ofstream out("output.txt");

    int M, L;

    in >> M >> L;

    adjacency_list_t GRAFO;
    GRAFO.resize(M);

    for(int i=0; i<	L;i++){
    	int tmp;
    	int dest;

    	in >> tmp;
    	in >> dest;
    	GRAFO[tmp].push_back(neighbor(dest));
    	GRAFO[dest].push_back(neighbor(tmp));

   }
for(int k=0;k<M;k++){
	cout << k << ": ";
	for(int t=0;t<GRAFO[k].size();t++)
	{
		cout << GRAFO[k][t].target << " " ;
	}
	cout << endl;

}







}
