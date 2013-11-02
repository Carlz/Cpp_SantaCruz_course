/* 
 * File:   Path.h
 * Author: Capacitare
 *
 * Created on November 1, 2013, 10:54 PM
 */

#include <iostream>
#include <vector>
#include "NodeData.h"
using namespace std;

#ifndef PATH_H
#define	PATH_H

// Path data structure
class Path {
public:
            Path(): cost(0.0) {}
            Path(const Path& orig): node_list(orig.node_list), cost(orig.cost) {}
            Path(vector<node> nodes, float n_cost, int dbg = 0): node_list(nodes), cost(n_cost) {}
    node    get_source() const {return node_list.front(); }
    node    get_dest() const {return node_list.back(); }
    void    add_node(node new_node, float edge_cost) {cost += edge_cost; node_list.push_back(new_node); }
    vector<node> get_path() const {return node_list; }
    size_t  get_size() const { return node_list.size(); }
    float   get_cost() const {return cost; }
    friend ostream& operator<<(ostream& out, const Path& data); // Prints PriorityQueue structure on the screen    
    
private:    
    vector<node> node_list;     // Path's nodes beginning from start node, ending by final node
    float cost;                 // Path's cost
};

#endif	/* PATH_H */

