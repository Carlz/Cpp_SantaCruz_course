////////////////////////////////////////////////////////////////////////////////
/// \brief      Path class definition.
/// \author     Carlos Sampaio
/// \file       Path.h
/// \date       01/11/2013
///
///     Path class definition.
///
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include "Graph_pkg.h"
using namespace std;

#ifndef PATH_H
#define	PATH_H

// Path data structure
class Path {
public:
    Path(): cost(0.0) {}                                                      // Trivial constructor
    Path(const Path& orig): node_list(orig.node_list), cost(orig.cost) {}     // Copy constructor
    Path(vector<node> nodes, float n_cost): node_list(nodes), cost(n_cost) {} // Complete constructor
    
    node    get_source() const {return node_list.front(); }     // Get path source node
    node    get_dest() const {return node_list.back(); }        // Get path destination node
    void    add_node(node new_node, float edge_cost);           // Add node in the end of the path
    vector<node> get_path() const {return node_list; }          // Get path node list
    size_t  get_size() const { return node_list.size(); }       // Get path size in number of nodes
    float   get_cost() const {return cost; }                    // Get path cost
    friend ostream& operator<<(ostream& out, const Path& data); // Prints Path structure on the screen
    
private:    
    vector<node> node_list;     // Path nodes beginning from start node, ending by final node
    cost_type cost;             // Path cost
};

#endif	/* PATH_H */

