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
    ShortestPath();
    ShortestPath(const ShortestPath& orig);
    virtual ~ShortestPath();
    
    vector<node> vertices();                    // list of vertices in G(V,E).
    Path         find_path(Graph& base_graph, node src, node dst);      // find shortest path between u-w and returns the sequence of vertices representing shorest path u-v1-v2-…-vn-w.
    float        path_size(node src, node dst); // return the path cost associated with the shortest path.

private:
    Graph search_graph;
    node last_src, last_dst;
    float path_cost;

};

#endif  /* SHORTESTPATH_H */

