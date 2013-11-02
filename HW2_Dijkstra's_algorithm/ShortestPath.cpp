/* 
 * File:   ShortestPath.cpp
 * Author: Capacitare
 * 
 * Created on October 27, 2013, 8:34 PM
 */

#include <assert.h>
#include "ShortestPath.h"

ShortestPath::ShortestPath(const ShortestPath& orig) {
}

ShortestPath::~ShortestPath() {
}

bool ShortestPath::find_path(Graph& base_graph, node src, node dst)
{
    if (debug_lvl > 2)
        cout << "Searching src: " << src << " dest: " << dst << endl;
    
    assert((src < base_graph.node_cnt()) && (dst < base_graph.node_cnt()));
    
    bool path_found = false;
    PriorityQueue close_set, open_set;
    Path close_path, return_path;
    vector<node> nb_list;    //neighbours
    bool empty_open_set = false;
    int iteration = 0;
    
    close_path.add_node(src, 0.0);
    close_set.insert(close_path);
    
    while ((close_path.get_dest() != dst) && !(empty_open_set))
    {
        if (debug_lvl > 2)
            cout << "Start iteration " << ++iteration << endl;
        node local_src = close_path.get_dest();
        nb_list =  base_graph.neighbours(local_src);
        for (size_t i = 0; i < nb_list.size(); ++i)
        { 
            Path new_path = close_path;
            new_path.add_node(nb_list[i], base_graph.get_edge_value(local_src, nb_list[i]));
            float open_cost = open_set.get_cost(nb_list[i]);            
            if (close_set.get_cost(nb_list[i]) < 0)                     // if node is not in the close set
            {
                if (open_cost < 0)                                      // if node is not in the open set
                    open_set.insert(new_path);                          // ... include its path
                else if (open_cost > new_path.get_cost())               // else node is in the open set, but with higher cost
                    open_set.chg_prioirity(new_path);                   // ... update node's path and cost
            }
        }
        if (open_set.size() > 0)
        {
            close_path = open_set.top();
            open_set.pop_top();
            close_set.insert(close_path);
        }
        else
            empty_open_set = true;
        
        if (debug_lvl > 2)
        {
            cout << "===========================" << endl;
            cout << "Close set:" << endl << close_set;
            cout << "Open set:" << endl << open_set;
        }
    }
    //
    if (close_path.get_dest() == dst)
    {
        if (debug_lvl > 0)
        {
            cout << "===========================" << endl;        
            cout << "Found Shortest Path: "; 
            for (size_t i = 0; i < close_path.get_path().size(); ++i)
                cout << close_path.get_path().at(i) << " ";
            cout << endl << "Cost: " << close_path.get_cost() << endl;
        }
        path_found = true;
        this->short_path = close_path;
    }
    else
    {
        this->short_path = Path();        
        if (debug_lvl > 0)
            cout << "No Path between nodes " << src << " and " << dst << "!" << endl;
    }

    return path_found;
}