////////////////////////////////////////////////////////////////////////////////
/// \brief      Dijkstra Shortest Path class implementation
/// \author     Carlos Sampaio
/// \file       ShortestPath.cpp
/// \date       27/10/2013
///
///     Dijkstra Shortest Path class implementation.
///
////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include "ShortestPath.h"

//// Main Dijkstra algorithm method. Get a graph, two nodes, and calculate the shortest path
//bool ShortestPath::find_path(Graph& base_graph, node src, node dst)
//{
//    if (debug_lvl > 2)
//        cout << "Searching src: " << src << " dest: " << dst << endl;
//    
//    assert((src < base_graph.node_cnt()) && (dst < base_graph.node_cnt()));
//    
//    bool path_found = false;                                    // Control if shortest path was found
//    PriorityQueue close_set(debug_lvl), open_set(debug_lvl);    // Open and Close sets queues
//    Path close_path;                                            // Close path, last chosen path
//    vector<edge_data> nb_list;                                  // Node neighbours list
//    bool empty_open_set = false;                                // Control if there are still option in open set
//    int iteration = 0;                                          // Number of iterations counter
//    node next_src = src;                                        // Next source for iterations
//    
//    close_path.add_node(src, 0.0);                              // Add source node in the close set
//    close_set.insert(close_path);
//    
//    // While destination node is not in the close set and there are still options in the open set, keep searching
//    while ((next_src != dst) && !(empty_open_set))
//    {
//        if (debug_lvl > 2)
//            cout << "Start iteration " << ++iteration << endl;
//
//        nb_list =  base_graph.neighbors(next_src);
//        for (edge_iterator it = nb_list.begin(); it != nb_list.end(); ++it)      // At each neighbour
//        { 
//            if (close_set.get_cost(it->first) < 0)              // check if node is not in the close set
//            {
//                Path new_path = close_path;                     // Create a new path with this destination
//                new_path.add_node(it->first, it->second);
//                cost_type open_cost = open_set.get_cost(it->first); // Check if node is in the open set
//                
//                if (open_cost < 0)                              // if node is not in the open set
//                    open_set.insert(new_path);                  // ... include its path
//                else if (open_cost > new_path.get_cost())       // else node is in the open set, but with higher cost
//                    open_set.chg_prioirity(new_path);           // ... update node's path and cost
//            }
//        }
//        if (open_set.size() > 0)                                // If there are still options in the open set
//        {
//            close_path = open_set.top();                        // Take the one with least cost to insert
//            open_set.pop_top();                                 // in close set, and be used in the next
//            close_set.insert(close_path);                       // iteration
//            next_src = close_path.get_dest();
//        }
//        else
//            empty_open_set = true;                              // If no more option in open set, finish computation
//        
//        if (debug_lvl > 2)
//        {
//            cout << "===========================" << endl;
//            cout << "Close set:" << endl << close_set;
//            cout << "Open set:" << endl << open_set;
//        }
//    }
//    //
//    if (close_path.get_dest() == dst)                           // If computation ended and close path destination
//    {                                                           // node is the searched node, than return success
//        if (debug_lvl > 0)                                      // and update object's shortest path
//        {
//            cout << "===========================" << endl;        
//            cout << "Found Shortest " << close_path; 
//        }
//        path_found = true;
//        this->short_path = close_path;
//    }
//    else                                                        // If no path was found, clear the shortest path
//    {
//        this->short_path = Path();        
//        if (debug_lvl > 0)
//            cout << "No Path between nodes " << src << " and " << dst << "!" << endl;
//    }
//
//    return path_found;
//}