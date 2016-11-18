#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>

using namespace std;

struct node {
	vector<int> neighbor;
	bool visited = false;
};

typedef vector<node> graph_t;
typedef pair<int, int> edge_t;
typedef vector<int> path_t;

void dfsExplore(graph_t& graph, int u, path_t& visitOrder, vector<path_t>& cyclesList);
vector<path_t> getCycles(graph_t& graph);
unsigned int countCommonEdges(path_t path1, path_t path2);
unsigned int mcd(unsigned int x, unsigned int y);

int main()
{
	int N, E;

	ifstream in("input.txt");
	in >> N >> E;

	graph_t graph(N);
	vector<edge_t> edges;

	for(int i = 0; i < E; i++)
	{
		int source, destination;
		in >> source >> destination;

		edge_t edge(source, destination);
		edges.push_back(edge);

		graph[source].neighbor.push_back(destination);
		graph[destination].neighbor.push_back(source);
	}

	vector<path_t> cycleList = getCycles(graph);

	unsigned int maxSpecies = cycleList[0].size();
	for(size_t i = 0; i < cycleList.size() - 1; i++)
	{
		unsigned int _maxSpecies = maxSpecies;
		maxSpecies = mcd(cycleList[i].size(), cycleList[i + 1].size());
		maxSpecies = mcd(maxSpecies, _maxSpecies);

		unsigned int commonEdgesCount =
			countCommonEdges(cycleList[i], cycleList[i + 1]);

		maxSpecies = mcd(
			maxSpecies,
			cycleList[i].size() + cycleList[i + 1].size() - commonEdgesCount
		);
	}

	vector<int> species(E);

	for(path_t cycle:cycleList)
	{
		int currentSpecie = 0;
		cycle.push_back(cycle[0]);
		for(size_t i = 0; i < cycle.size() - 1; i++)
		{
			currentSpecie %= maxSpecies;

			int n1, n2;
			n1 = cycle[i];
			n2 = cycle[i + 1];

			if(n1 > n2)
			{
				swap(n1, n2);
			}

			pair<int, int> edge = make_pair(n1, n2);
			unsigned int pos = find(edges.begin(), edges.end(), edge) - edges.begin();
			species[pos] = currentSpecie;

			currentSpecie++;
		}
	}

	ofstream out("output.txt");

	out << maxSpecies << endl;

	for(int specie:species)
		out << specie << endl;

	out.close();

	return 0;
}

void dfsExplore(graph_t& graph, int u, vector<int>& visitOrder, vector<vector<int>>& cyclesList)
{
	graph[u].visited = true;
	for(int node:graph[u].neighbor)
		if(!graph[node].visited && !(graph[node].neighbor.empty()))
		{
			visitOrder.push_back(node);
			dfsExplore(graph, node, visitOrder, cyclesList);
			visitOrder.pop_back();
		}
		else
		{
			if(node != visitOrder[visitOrder.size() - 2])
			{
				unsigned int pos = find(
					visitOrder.begin(),
					visitOrder.end(),
					node) - visitOrder.begin();

				path_t toPush(visitOrder.begin() + pos, visitOrder.end());

				if(!toPush.empty())
					cyclesList.push_back(toPush);
			}
		}
}

vector<path_t> getCycles(graph_t& graph)
{
	vector<path_t> cyclesList;
	path_t visitOrder;

	for(size_t node = 0; node < graph.size(); node++)
		if(!graph[node].visited)
		{
			visitOrder.push_back(node);
			dfsExplore(graph, node, visitOrder, cyclesList);
		}

	return cyclesList;
}

unsigned int countCommonEdges(path_t path1, path_t path2)
{
	unsigned int count = 0;
	for(int n1:path1)
		for(int n2:path2)
			if(n1 == n2)
				count++;

	return (count > 0) ? count - 1 : 0;
}

unsigned int mcd(unsigned int x, unsigned int y)
{
	while(y != 0)
	{
		unsigned int z = x % y;
		x = y;
		y = z;
	}

	return x;
}
