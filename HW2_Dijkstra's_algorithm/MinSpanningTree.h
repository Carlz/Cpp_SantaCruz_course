////////////////////////////////////////////////////////////////////////////////
/// \brief      Minimum Spanning Tree class definition.
/// \author     Carlos Sampaio
/// \file       MinSpanningTree.h
/// \date       27/10/2013
///
///     Minimum Spanning Tree class definition.
///
////////////////////////////////////////////////////////////////////////////////

#include "Graph_pkg.h"
#include "Graph.h"
#include "PriorityQueue.h"

#ifndef MINSPANNINGTREE_H
#define MINSPANNINGTREE_H

class MinSpanningTree {
public:
    MinSpanningTree(int debug_lvl = 0): debug_lvl(debug_lvl) {}    
   
    bool find_prim_tree(Graph& base_graph); // find minimum spanning tree in base_graph using Prim's algorithm
                                            // returns true on success, false on fail
    size_t get_size() const {return min_tree.size();}  // tree node size for last minimum spanning tree found.
//  cost_type get_cost() const {return min_tree.get_cost();}  // return the minimum spanning tree cost from the last found
    PriorityQueue get_tree() const {return min_tree;}         // return the path nodes associated with last shortest path found.

private:
    PriorityQueue min_tree;    // Last minimum spanning tree found
    int  debug_lvl;            // Object debug level
};

#endif  /* MINSPANNINGTREE_H */

