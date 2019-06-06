/************************************************************************************************
						HOMEWORK 7: Kruskal's Algorithm Implementation
						Scott Klinn
						CS 350: Algorithms
						David Ely, Spring 2019

/*************************************************************************************************/

//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include "Edge.h"
#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;


#define INF  1000000
// infinity

// The adjacency matrix for the graph :
int N; // number of nodes (vertices)
int A[100][100]; // adjacency matrix of the graph
int B[100][100];
vector<int> parent;



/* This function facilitates the start of the Kruskal algorithm, and each vertex of the graph is set as its own subtree. */


void MakeSet(int vert)
{
	parent[vert] = vert;

	return;
}



/* The Find() function traces through to find the root of the subtree; this is used to determine whether a cycle condition will exist. */


int Find(int i)
{
	if (i == parent[i])
		return i;
	
	return Find(parent[i]);
}


/* The Union() function consolidates subtrees as edges connect the subtrees together. */


void Union(int x, int y) 
{
	parent[x] = parent[y];

	return;
}


/* This function handles the reading in of the adjacency matrix file from the command line. */


void input_graph()
{
	int r, c;
	char w[10];

	cin >> N;

	// scan the first row of labels....not used
	for (c = 0; c < N; c++) {
		cin >> w;
	}


	for (r = 0; r < N; r++) {
		cin >> w; // label ... not used
		for (c = 0; c < N; c++) {
			cin >> w;
			if (w[0] == '-') {
				A[r][c] = -1;
			}
			else {
				A[r][c] = atoi(w);// ascii to integer
			}

		}
	}
}


/* The print_graph prints the passed graph argument to the console. '-' will populate where -1 is encoded that signifies no edge connection. */


void print_graph(int graph[][100])
{
	int r, c;

	cout << endl << endl << N << endl;

	cout << "  ";
	for (c = 0; c < N; c++) {
		printf("   %c", c + 'A');
	}

	cout << endl;

	for (r = 0; r < N; r++) {
		printf("%c  ", r + 'A');
		for (c = 0; c < N; c++) {
			if (graph[r][c] == -1) {
				printf("  - ");
			}
			else {
				printf("%3d ", A[r][c]);
			}
		}
		cout << endl;
	}
	cout << endl;
}


/* The ReadEdges() function cycles through the adjacency matrix file to create the Edge objects and loads them into the Edge vector. */


void ReadEdges(vector<Edge>& Edges)
{
	Edge temp;
	for (int r = 0; r < N; r++) {
		for (int c = r + 1; c < N; c++) {
			if (A[r][c] == -1)
				continue;
			temp = Edge(A[r][c], c + 'A', r + 'A');
			Edges.push_back(temp);
		}
	}

	return;
}


/* MergeSort() should be a fairly self-explanatory function. Sorts the Edge objects from lowest to heighest weight value. */


void MergeSort(vector<Edge>& Edges)
{
	if (Edges.size() < 2)
		return;

	int middle = Edges.size() / 2;
	vector<Edge> L_Edges(Edges.begin(), Edges.begin() + middle);
	vector<Edge> R_Edges(Edges.begin() + middle, Edges.end());
	MergeSort(L_Edges);
	MergeSort(R_Edges);

	auto l = L_Edges.begin();
	auto r = R_Edges.begin();

	for (auto it = Edges.begin(); it != Edges.end(); ++it) {
		if (l != L_Edges.end() && (r == R_Edges.end() || *r > *l)) {
			*it = *l;
			++l;
		}
		else {
			*it = *r;
			++r;
		}
	}

	return;
}



/* The init_graph() is an auxiliary function to initialize B, the graph to represent the minimum spanning tree. */


void init_graph()
{
	int r, c;

	for (r = 0; r < N; r++) {
		for (c = 0; c < N; c++) {
			B[r][c] = -1;
		}
	}
	
	return;
}



/* disjoint() is a basic function for Kruskal's algorithm that notes whether two subtrees are disjoint by comparing the tree's roots. */


bool disjoint(int x, int y)
{ 
	return x != y;
}


/* This is the main Kruskal's algorithm implementation. Returns the number of Edges that exist in the minimum spanning tree. */


int kruskal(vector<Edge>& Edges, vector<Edge>& Tree)
{
	// Each vector of Edges will correspond to one of the N vertices of the graph
	parent.resize(N);
	for (int i = 0; i < N; ++i)
		MakeSet(i);

	int x, y;
	int size = 0;

	for (Edge item : Edges) {
		x = Find(item.get_vertx());
		y = Find(item.get_verty());
		if (disjoint(x, y)) {
			Tree.push_back(item);
			++size;
			Union(x, y);
		}
	}

	return size;
}


/* The tree_to_graph() function sequentially goes through the minimum spanning tree vector and updates array B with the weights of the edges. */


int tree_to_graph(vector<Edge>& Tree)
{
	int x, y;

	for (Edge item : Tree) {
		x = item.get_vertx();
		y = item.get_verty();
		B[x][y] = item.get_weight();
		B[y][x] = item.get_weight();
	}

	return 0;
}



int main()
{
	input_graph();// N, A{}{}  
	print_graph(A);

	vector<Edge> GraphEdges;
	vector<Edge> SpanTree;

	ReadEdges(GraphEdges);

	cout << "Unsorted Edges from Graph: " << endl;
	for (Edge item : GraphEdges) {
		item.display();
		cout << " ";
	}
	MergeSort(GraphEdges);
	cout << endl << "After sorting...: " << endl;
	for (Edge item : GraphEdges) {
		item.display();
		cout << " ";
	}

	init_graph();
	cout << endl << "Number of edges in minimal spanning tree is " << kruskal(GraphEdges, SpanTree) << " edge(s). These are..." << endl;
	
	int weight = 0;
	
	for (Edge item : SpanTree) {
		weight += item.get_weight();
		item.display();
		cout << " ";
	}

	tree_to_graph(SpanTree);
	print_graph(B);

	cout << endl << "Minimal spanning tree's weight total is " << weight << "." << endl;

	return 0;
}