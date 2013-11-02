/* 
 * File:   ShortestPath.h
 * Author: Capacitare
 *
 * Created on October 27, 2013, 8:34 PM
 */

#include "Graph.h"
#include "PriorityQueue.h"

#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

class ShortestPath {
public:
    ShortestPath(int debug_lvl = 0): debug_lvl(debug_lvl) {}
    ShortestPath(const ShortestPath& orig);
    virtual ~ShortestPath();
    
    vector<node> vertices();                    // list of vertices in G(V,E).
    bool         find_path(Graph& base_graph, node src, node dst);      // find shortest path between u-w and returns the sequence of vertices representing shorest path u-v1-v2-…-vn-w.
    size_t       get_size() const {return short_path.get_size();} // return the path cost associated with the shortest path.
    float        get_cost() const {return short_path.get_cost();}
    Path         get_path() const {return short_path;}

private:
    Path short_path;
    int  debug_lvl;

};

#endif  /* SHORTESTPATH_H */

