#include <iostream>
#include <vector>
#define MAX 100000
using namespace std;

struct node
{
	int wt, parent;
	bool visited;
	vector <int> adj, wts;
};

class Graph
{
public:
	vector <node> nodes;
	Graph(int n)
	{
		nodes.resize(n);
		for (int i = 0; i < n; ++i)
		{
			nodes[i].wt = MAX;
			nodes[i].visited = false;
		}
	}

	void addEdge(int a, int b, int val)
	{
		nodes[a].adj.push_back(b);
		nodes[b].adj.push_back(a);
		nodes[a].wts.push_back(val);
		nodes[b].wts.push_back(val);
	}

	void prims()
	{
		nodes[0].wt = 0;
		int cur, treeSize = 0;
		while (treeSize != nodes.size())
		{
			cur = getNextMinimumVertex();
			nodes[cur].visited = true;
			for (int i = 0; i < nodes[cur].adj.size(); ++i)
			{
				if (nodes[nodes[cur].adj[i]].wt > nodes[cur].wts[i] + nodes[cur].wt)
				{
					nodes[nodes[cur].adj[i]].wt = nodes[cur].wts[i] + nodes[cur].wt;
					nodes[nodes[cur].adj[i]].parent = cur;
				}
			}
			treeSize++;
		}
		for (int i = 0; i < nodes.size(); ++i) 
			if (nodes[i].parent != i)			
			// since we start MST from 0, it's parent would be undefined, so chucks this and print rest
				cout << i << " --- " << nodes[i].parent << endl;
	}

	// to make it priority queue you have to modify only this function to get the minimum from a heap 
	int getNextMinimumVertex()
	{
		int minwt = MAX, minpos = 0;
		for (int i = 0; i < nodes.size(); ++i)
		{
			if (nodes[i].visited == false && nodes[i].wt <= minwt)
			{
				minwt = nodes[i].wt;
				minpos = i;
			}
		}
		return minpos;
	}
};

int main()
{
	int m,n;
	cout << "Enter no. of vertices: ";
	cin >> n;
	Graph G(n);
	cout << "Enter no. of Edges: ";
	cin >> m;
	cout << "Enter < a, b, wt > for each edge:\n";
	for (int i = 0,a,b,val; i < m; ++i)
	{
		cin >> a >> b >> val;
		G.addEdge(a,b,val);
	}
	G.prims();
	return 0;
}