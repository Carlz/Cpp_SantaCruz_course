////////////////////////////////////////////////////////////////////////////////
/// \brief      Package with Graph types
/// \author     Carlos Sampaio
/// \file       Graph_pkg.cpp
/// \date       02/11/2013
///
///     Types definitions used in different structures involving Graphs.
///
////////////////////////////////////////////////////////////////////////////////

#include <vector>
using namespace std;

#ifndef GRAPH_PKG_H
#define	GRAPH_PKG_H

typedef unsigned short int node;            // Node index type
typedef float cost_type;                    // Edge and Node cost type

typedef pair<node, cost_type> edge_data;    // Edge data: First = destination node, second = edge cost
typedef vector<edge_data> node_data;        // List of node edges

typedef vector<node_data>::iterator node_iterator;              // Iterator for nodes
typedef vector<node_data>::const_iterator node_const_iterator;  // Constant Iterator for nodes

typedef vector<edge_data>::iterator edge_iterator;              // Iterator for edges
typedef vector<edge_data>::const_iterator edge_const_iterator;  // Constant Iterator for edges

#endif	/* GRAPH_PKG_H */

