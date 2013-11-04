////////////////////////////////////////////////////////////////////////////////
/// \brief      Dijkstra Shortest Path class definition.
/// \author     Carlos Sampaio
/// \file       ShortestPath.h
/// \date       27/10/2013
///
///     Dijkstra Shortest Path class definition.
///
////////////////////////////////////////////////////////////////////////////////

#include "Graph_pkg.h"
#include "Graph.h"
#include "PriorityQueue.h"

#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

class ShortestPath {
public:
    ShortestPath(int debug_lvl = 0): debug_lvl(debug_lvl) {}    
   
    bool      find_path(Graph& base_graph, node src, node dst); // find shortest path between src-dst in base_graph 
                                                                // returns true on success, false on fail
    size_t    get_size() const {return short_path.get_size();}  // return the path size associated with last shortest path found.
    cost_type get_cost() const {return short_path.get_cost();}  // return the path cost associated with last shortest path found.
    Path      get_path() const {return short_path;}             // return the path nodes associated with last shortest path found.

private:
    Path short_path;    // Last shortest path found
    int  debug_lvl;     // Object debug level
};

#endif  /* SHORTESTPATH_H */

