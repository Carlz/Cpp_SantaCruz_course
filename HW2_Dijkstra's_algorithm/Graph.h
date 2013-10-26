////////////////////////////////////////////////////////////////////////////////
/// \brief      Graph class definition
/// \author     Carlos Sampaio
/// \file       Graph.cpp
/// \date       20/10/2013
///
///     Graph class definition.
///
////////////////////////////////////////////////////////////////////////////////

#include <vector>
using namespace std;

#ifndef GRAPH_H
#define	GRAPH_H

// Edge data structure
struct edge_data {
    int dest_node;     // Edge´s destination node
    int cost;          // Edge´s cost
};

// Node data structure
struct node_data {
    vector<edge_data> edges;      // Edge list to node's neighbours
    int value;                    // Node value
};

typedef int node;   // Node index type


class Graph {
public:
            Graph() {}                      // Trivial constructor.
            Graph(int node_number) { nodes.resize(node_number);} // Initialize Graph with n nodes.
    int     node_cnt() { return nodes.size();} // Returns the number of nodes in the graph.
    int     edge_cnt();                     // Returns the number of edges in the graph.
    bool    adjacent(node x, node y);       // Tests whether there is an edge from node x to node y.
    vector<node> neighbours(node x);        // Lists all nodes y such that there is an edge from x to y.
    void    add_edge(node x, node y, int cost); // Adds the edge from x to y with cost, if it is not there.
    void    delete_edge(node x, node y);    // Removes the edge from x to y, if it is there.
    int     get_node_value(node x);         // Returns the value associated with the node x.
    void    set_node_value(node x, int val);// Sets the value associated with the node x.
    int     get_edge_value(node x, node y); // Returns the value associated to the edge (x,y).
    void    set_edge_value (node x, node y, int cost); //Sets the cost associated to the edge (x,y).

private:
    vector<node_data> nodes;                // Graph's nodes list.
    void    delete_edge_uni(node x, node y);
    void    set_edge_value_uni(node x, node y, int cost);

};

#endif	/* GRAPH_H */

