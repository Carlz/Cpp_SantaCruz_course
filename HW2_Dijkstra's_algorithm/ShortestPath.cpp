/* 
 * File:   ShortestPath.cpp
 * Author: Capacitare
 * 
 * Created on October 27, 2013, 8:34 PM
 */

#include <assert.h>
#include "ShortestPath.h"

ShortestPath::ShortestPath() {
}

ShortestPath::ShortestPath(const ShortestPath& orig) {
}

ShortestPath::~ShortestPath() {
}

vector<node> ShortestPath::find_path(Graph& base_graph, node src, node dst)
{
    assert(src < base_graph.node_cnt() && dst < base_graph.node_cnt());
    
    PriorityQueue close_set, open_set;
    Path tmp_path;
    vector<node> tmp_nb;    //neighbours
    
    tmp_path.add_node(src, 0.0);
    close_set.insert(tmp_path);
    tmp_nb = base_graph.neighbours(src);
    for (int i = 0; i < tmp_nb.size(); ++i)
    {
        Path new_path = tmp_path;
        new_path.add_node(tmp_nb[i], base_graph.get_edge_value(src, tmp_nb[i]));
        open_set.insert(new_path);
    }
    cout << "Close set: \n" << close_set;
    cout << "Open set: \n" << open_set;
}