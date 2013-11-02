////////////////////////////////////////////////////////////////////////////////
/// \brief      Graph class definition
/// \author     Carlos Sampaio
/// \file       Graph.cpp
/// \date       20/10/2013
///
///     Graph class definition.
///
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <vector>
#include "NodeData.h"
using namespace std;

#ifndef GRAPH_H
#define	GRAPH_H

class Graph {
public:
            Graph(int nd_cnt = 0) { if (nd_cnt > 0) nodes.resize(nd_cnt);} ///< Initialize Graph with nd_cnt nodes.
    void    randomize(unsigned int nd_cnt = 0, float density = 0,
                      float cost_low = 1.0, float cost_high = 10.0); ///< Generate a random graph structure base on node count and edge density
    int     node_cnt() const { return nodes.size();}      // Returns the number of nodes in the graph.
    int     edge_cnt() const;               // Returns the number of edges in the graph.
    bool    adjacent(node x, node y) const ;  // Tests whether there is an edge from node x to node y.
    vector<node> neighbours(node x) const;        // Lists all nodes y such that there is an edge from x to y.
    void    add_edge(node x, node y, float cost); // Adds the edge from x to y with cost, if it is not there.
    void    delete_edge(node x, node y);    // Removes the edge from x to y, if it is there.
    float   get_node_value(node x) const;         // Returns the value associated with the node x.
    void    set_node_value(node x, float val);// Sets the value associated with the node x.
    float   get_edge_value(node x, node y) const; // Returns the value associated to the edge (x,y).
    void    set_edge_value (node x, node y, float cost); //Sets the cost associated to the edge (x,y).
    void    destroy();                      // Clear all graph structure
    friend ostream& operator<<(ostream& out, const Graph& data); // Prints Graph structure on the screen


private:
    void    delete_edge_uni(node x, node y);
    void    set_edge_value_uni(node x, node y, float cost);
    void    add_random_edge(node src, node dst, float density, float cost_low, float cost_high);
    inline float random_cost(float low, float high) const;
    
    // Edge data structure
    struct edge_data {
        node dest_node;             // Edge´s destination node
        float cost;                 // Edge´s cost
    };

    // Node data structure
    struct node_data {
        vector<edge_data> edges;    // Edge list to node's neighbours
        float value;                // Node value
    };

    typedef vector<node_data>::iterator node_iterator;
    typedef vector<edge_data>::iterator edge_iterator;

    vector<node_data> nodes;                // Graph's nodes list.
    
};

#endif	/* GRAPH_H */

