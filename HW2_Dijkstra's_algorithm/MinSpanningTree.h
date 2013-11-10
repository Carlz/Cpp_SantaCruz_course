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
   
    bool find_prim_tree(Graph& base_graph);             // Searches for the minimum spanning tree in base_graph using Prim's algorithm
                                                        // ... and returns true on success, false on fail
    size_t get_size() const {return min_tree.size();}   // Returns the size in number of edges of the last minimum spanning tree found.
    cost_type get_cost() const;                         // Returns the cost of the last minimum spanning tree found.
    vector<Path> get_tree() const {return min_tree;}    // Returns the edges of the last minimum spanning tree found.
    void print_tree() const;                            // Prints the last minimum spanning tree found.

private:
    vector<Path> min_tree;                              // Last minimum spanning tree found
    int  debug_lvl;                                     // Object debug level
};

#endif  /* MINSPANNINGTREE_H */

