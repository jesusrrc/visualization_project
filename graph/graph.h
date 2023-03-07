
// Double inclusion guards.
#ifndef GRAPH_H
#define GRAPH_H

// C++ libraries.
#include <iostream>
#include <vector>
// Standard C++ namespace.
using namespace std;

class Graph
{
	public:
		Graph();
		Graph( const int n );
		void add_edge( const int a, const int b );	
	private:
		vector<vector<int>> adj_matrix;
		int adj_matrix_size;
};

#endif
