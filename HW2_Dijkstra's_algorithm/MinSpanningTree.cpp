////////////////////////////////////////////////////////////////////////////////
/// \brief      Minimum Spanning Tree class implementation.
/// \author     Carlos Sampaio
/// \file       MinSpanningTree.cpp
/// \date       27/10/2013
///
///     Minimum Spanning Tree class implementation. Implements Prim's algorithm
///
////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include "MinSpanningTree.h"
#include "Graph.h"
#include "PriorityQueue.h"

// Main Prim's algorithm method. Get a graph and calculate the minimum spanning tree
bool MinSpanningTree::find_prim_tree(Graph& base_graph)
{
    
    bool tree_found = false;                                    // Control if minimum spanning tree was found
    PriorityQueue close_set(debug_lvl), open_set(debug_lvl);    // Open and Close sets queues
    Path close_edge;                                            // Close edge, last chosen edge
    vector<edge_data> nb_list;                                  // Node neighbors list
    bool empty_open_set = false;                                // Control if there are still option in open set
    int iteration = 0;                                          // Number of iterations counter
    node next_src = 0;                                          // Next source for iterations
    
    close_edge.add_node(next_src, 0.0);                         // Add source node in the close set
    close_set.insert(close_edge);
    
    // While destination node is not in the close set and there are still options in the open set, keep searching
    while ((close_set.size() < base_graph.node_cnt()) && !(empty_open_set))
    {
        if (debug_lvl > 2)
            cout << "Start iteration " << ++iteration << endl;

        nb_list =  base_graph.neighbors(next_src);
        for (edge_iterator it = nb_list.begin(); it != nb_list.end(); ++it)      // At each neighbor
        { 
            if (close_set.get_cost(it->first) < 0)              // check if node is not in the close set
            {
                Path new_path;                                  // Create a new path with this destination
                new_path.add_node(next_src, 0.0);
                new_path.add_node(it->first, it->second);
                cost_type open_cost = open_set.get_cost(it->first); // Check if node is in the open set
                
                if (open_cost < 0)                              // if node is not in the open set
                    open_set.insert(new_path);                  // ... include its path
                else if (open_cost > new_path.get_cost())       // else node is in the open set, but with higher cost
                    open_set.chg_prioirity(new_path);           // ... update node's path and cost
            }
        }
        if (open_set.size() > 0)                                // If there are still options in the open set
        {
            close_edge = open_set.top();                        // Take the one with least cost to insert
            open_set.pop_top();                                 // in close set, and be used in the next
            close_set.insert(close_edge);                       // iteration
            next_src = close_edge.get_dest();
        }
        else
            empty_open_set = true;                              // If no more option in open set, finish computation
        
        if (debug_lvl > 2)
        {
            cout << "===========================" << endl;
            cout << "Close set:" << endl << close_set;
            cout << "Open set:" << endl << open_set;
        }
    }
    //
    if (close_set.size() == base_graph.node_cnt())            // If computation ended and close path destination
    {                                                           // node is the searched node, than return success
        if (debug_lvl > 0)                                      // and update object's minimum spanning tree
        {
            cout << "===========================" << endl;        
            cout << "Found Minimum Spanning Tree " << close_set; 
        }
        tree_found = true;
        this->min_tree = close_set;
    }
    else                                                        // If no path was found, clear the minimum spanning tree
    {
        this->min_tree = PriorityQueue();        
        if (debug_lvl > 0)
            cout << "No complete Spanning Tree for graph" << endl;
    }

    return tree_found;
}