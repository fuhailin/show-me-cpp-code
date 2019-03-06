// C++ program to print DFS traversal from
// a given vertex in a  given graph
#include <iostream>
#include <set>
#include <queue>
using namespace std;

// data structure to store graph edges
struct Edge
{
	int src, dest;
	// compare for order.
	bool operator<(const Edge &pt) const
	{
		return (src < pt.src) || ((!(pt.src < src)) && (dest < pt.dest));
	}
};

// Unweighted Graph class represents a directed graph
// using adjacency list representation
class Graph
{
	int V; // No. of vertices

	// Pointer to an array containing adjacency lists
	set<int> *adjList;

	// A recursive function used by DFS
	void DFSUtil(int v, bool visited[]);

  public:
	// Constructor
	Graph(set<Edge> const &edges, int N)
	{
		V = N;
		adjList = new set<int>[N];
		// add edges to the undirected graph
		for (auto &edge : edges)
		{
			int src = edge.src;
			int dest = edge.dest;
			adjList[src].insert(dest);
			adjList[dest].insert(src); // Uncomment below line for undirected graph
		}
	}

	void printGraph(Graph const &graph, int N);

	// function to add an edge to graph
	void addEdge(int v, int w);

	// DFS traversal of the vertices reachable from v
	void DFS(int v);

	// BFS traversal of the vertices reachable from v
	void BFS(int v);

	// Destructor
	~Graph()
	{
		delete[] adjList; // Deallocate the memory
	}
};

void Graph::addEdge(int v, int w)
{
	//const bool is_in = adjList.find(v) != adjList.end();
	adjList[v].insert(w);
}

void Graph::DFSUtil(int v, bool visited[])
{
	// Mark the current node as visited and print it
	visited[v] = true;
	cout << v << " ";

	// Recur for all the vertices adjacent
	// to this vertex
	set<int>::iterator i;
	for (i = adjList[v].begin(); i != adjList[v].end(); ++i)
		if (!visited[*i])
			DFSUtil(*i, visited);
}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Graph::DFS(int v)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function
	// to print DFS traversal
	DFSUtil(v, visited);
}

void Graph::BFS(int u)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	queue<int> q;

	q.push(u);
	visited[u] = true;

	while (!q.empty())
	{
		int f = q.front();
		q.pop();
		cout << f << " ";
		// Enqueue all adjacent of f and mark them visited
		for (auto i = adjList[f].begin(); i != adjList[f].end(); i++)
		{
			if (!visited[*i])
			{
				q.push(*i);
				visited[*i] = true;
			}
		}
	}
}

// print adjacency list representation of graph
void Graph::printGraph(Graph const &graph, int N)
{
	for (int i = 0; i < N; i++)
	{
		// print current vertex number
		cout << i << " --> ";

		// print all neighboring vertices of vertex i
		for (int v : graph.adjList[i])
			cout << v << " ";
		cout << endl;
	}
}

int main()
{
	// // vector of graph edges
	// vector<Edge> edges;
	// int a, b, N;
	// while (!cin.eof())
	// {
	// 	cin >> a >> b;
	// 	Edge edge = {a, b};
	// 	edges.push_back(edge);
	// 	N = max(N, max(a, b));
	// }

	// vector of graph edges as per above diagram.
	// Please note that initialization vector in below format will
	// work fine in C++11, C++14, C++17 but will fail in C++98.
	set<Edge> edges =
		{{0, 1}, {1, 2}, {2, 0}, {2, 1}, {3, 2}, {4, 5}, {5, 4}};
	// Number of nodes in the graph
	int N = 6;

	// construct graph
	Graph g(edges, N);

	// print adjacency list representation of graph
	g.printGraph(g, N);

	g.addEdge(0, 1);
	g.addEdge(5, 3);
	/*g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);*/
	//g.addEdge(6, 0);

	cout << "**** after addEdge******" << endl;

	g.printGraph(g, N);

	cout << "Following is Depth First Traversal"
			" (starting from vertex 5) \n";
	g.DFS(5);
	cout << endl;
	cout << "Following is Breadth First Traversal"
			" (starting from vertex 5) \n";
	g.BFS(5);

	return 0;
}