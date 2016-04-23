#include <iostream>
#include <vector>
#define MAX 100000
using namespace std;

struct node
{
	int wt, parent, id;
	bool visited;
	vector <int> adj, wts;
};

class MinHeap
{
public:
	vector <node> nodes;
	int size;
	MinHeap()
	{
		nodes.resize(100);
		size = 1;	// 1 indexed heap
	}

	void insert(node x)
	{
		nodes[size] = x;
		size++;
		heapifyup(size - 1); // put the new element into the right place in heap
	}

	void heapifyup(int in)
	{
		while (in > 0 && parent(in) > 0 && nodes[parent(in)].wt > nodes[in].wt)
		{
			node temp = nodes[in];
			nodes[in] = nodes[parent(in)];
			nodes[parent(in)] = nodes[in];
			in = parent(in);
		}
	}

	void heapifydown(int in)
	{
		while (in < size && getMinChild(in) != MAX)
		{
			int child = getMinChild(in);
			node temp = nodes[in];
			nodes[in] = nodes[child];
			nodes[child] = temp;
			in = child;
		}
	}

	int extractMin()
	{
		// copy last element to first index, decrement size, heapifydown(firstelement)
		int minVertex = nodes[1].id;
		nodes[1] = nodes[size - 1];
		size--;
		heapifydown(1);
		return minVertex;
	}

	int parent(int x)
	{
		return (x > 0?x/2:0);
	}

	int getMinChild(int x)
	{
		int left = MAX, right = MAX;
		if (2*x < size && nodes[2*x].wt < nodes[x].wt) left = 2*x;
		if (2*x + 1 < size && nodes[2*x + 1].wt < nodes[x].wt) right = 2*x + 1;

		if (left == MAX) return right;
		if (right == MAX) return left;
		return nodes[left].wt < nodes[right].wt?left:right;
	}
};

// almost same thing as without priority queue implementation
class Graph
{
public:
	vector <node> nodes;
	MinHeap heap;
	Graph(int n)
	{
		nodes.resize(n);
		for (int i = 0; i < n; ++i)
		{
			nodes[i].wt = MAX;
			nodes[i].visited = false;
			nodes[i].id = i;
			heap.insert(nodes[i]);
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
			cur = heap.extractMin();
			while (nodes[cur].visited)
				cur = heap.extractMin();
			nodes[cur].visited = true;
			for (int i = 0; i < nodes[cur].adj.size(); ++i)
			{
				if (nodes[nodes[cur].adj[i]].wt > nodes[cur].wts[i] + nodes[cur].wt)
				{
					nodes[nodes[cur].adj[i]].wt = nodes[cur].wts[i] + nodes[cur].wt;
					nodes[nodes[cur].adj[i]].parent = cur;
					heap.insert(nodes[nodes[cur].adj[i]]);
				}
			}
			treeSize++;
		}
		for (int i = 0; i < nodes.size(); ++i) 
			if (nodes[i].parent != i)			
			// since we start MST from 0, it's parent would be undefined, so chucks this and print rest
				cout << i << " --- " << nodes[i].parent << endl;
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
