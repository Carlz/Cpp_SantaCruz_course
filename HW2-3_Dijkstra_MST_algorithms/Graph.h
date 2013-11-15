////////////////////////////////////////////////////////////////////////////////
/// \brief      Graph class definition
/// \author     Carlos Sampaio
/// \file       Graph.cpp
/// \date       20/10/2013
///
///     Graph class implements an undirected Graph with positive costs.
///
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <vector>
#include "Graph_pkg.h"
using namespace std;

#ifndef GRAPH_H
#define	GRAPH_H

class Graph {
public:
    Graph(size_t nd_cnt = 0);                                         // Initialize Graph with nd_cnt nodes.
    Graph(size_t nd_cnt, float density, cost_type cost_low, cost_type cost_high) // Initializae Graph with a random structure
        { this->randomize(nd_cnt, density, cost_low, cost_high);}
    Graph(string in_file);                                            // Initialize Graph with external input file
           
    void    randomize(unsigned int nd_cnt = 0, float density = 0,     // Generate a random graph structure base on
                      cost_type cost_low = 1.0, cost_type cost_high = 10.0);  // node count, edge density and cost.
    void    destroy();                                                // Clear all graph structure    
    int     node_cnt() const { return nodes.size();}                  // Returns the number of nodes in the graph.
    int     edge_cnt() const;                                         // Returns the number of edges in the graph.
    bool    adjacent(node src, node dst) const ;    // Tests whether there is an edge from node src to node dst.
    vector<edge_data> neighbors(node src) const;   // Lists all nodes dst such that there is an edge from src to dst.
    void    add_edge(node src, node dst, cost_type cost); // Adds the edge from src to dst with cost, if it is not there.
    void    delete_edge(node src, node dst);        // Removes the edge from src to dst, if it is there.
    cost_type get_node_value(node src) const;       // Returns the value associated with the node src.
    void    set_node_value(node src, cost_type val);// Sets the value associated with the node src.
    cost_type get_edge_value(node src, node dst) const;          // Returns the value associated to the edge (src,dst).
    void    set_edge_value (node src, node dst, cost_type cost); //Sets the cost associated to the edge (src,dst).
    friend  ostream& operator<<(ostream& out, const Graph& data);// Prints Graph structure on the screen


private:
    void    delete_edge_uni(node src, node dst);                      // Delete unidirectional edge
    void    set_edge_value_uni(node src, node dst, cost_type cost);   // Set unidirectional edge cost
    void    add_random_edge(node src, node dst, float density,
                            cost_type cost_low, cost_type cost_high); // Add a random edge for given density and cost range
    inline  cost_type random_cost(cost_type low, cost_type high) const; // Produces a random cost
    
    vector<node_data> nodes;                // Graph's nodes list.
    vector<cost_type> node_values;          // Graph's nodes Values
    
};

#endif	/* GRAPH_H */

