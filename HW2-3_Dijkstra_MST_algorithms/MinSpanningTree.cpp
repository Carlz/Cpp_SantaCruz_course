////////////////////////////////////////////////////////////////////////////////
/// \brief      Minimum Spanning Tree class implementation.
/// \author     Carlos Sampaio
/// \file       MinSpanningTree.cpp
/// \date       27/10/2013
///
///     Minimum Spanning Tree class implementation. Implements Prim's algorithm
///
////////////////////////////////////////////////////////////////////////////////

#include <iomanip>
#include "MinSpanningTree.h"

// Main Prim's algorithm method. Get a graph and calculate the minimum spanning tree
bool MinSpanningTree::find_prim_tree(Graph& base_graph)
{
    
    bool tree_found = false;                                    // Control if minimum spanning tree was found
    PriorityQueue close_set(debug_lvl), open_set(debug_lvl);    // Open and Close sets queues
    Path close_edge;                                            // Close edge, last chosen edge
    vector<edge_data> nb_list;                                  // Node neighbors list
    bool empty_open_set = false;                                // Control if there are still option in open set
    int iteration = 0;                                          // Number of iterations counter
    node next_src = 0;                                          // Next source for iterations, start on zero
    
    this->min_tree.clear();                                     // Clear current MST
    
    close_edge.add_node(next_src, 0.0);                         // Add source node in the close set
    close_set.insert(close_edge);
    
    // While destination node is not in the close set and there are still options in the open set, keep searching
    while ((close_set.size() < base_graph.node_cnt()) && !(empty_open_set))
    {
        if (debug_lvl > 2)
            cout << "Start iteration " << ++iteration << endl;

        nb_list =  base_graph.neighbors(next_src);
        for (edge_iterator it = nb_list.begin(); it != nb_list.end(); ++it)  // At each neighbor
        { 
            if (close_set.get_cost(it->first) < 0)                  // Check if node is not in the close set
            {
                cost_type open_cost = open_set.get_cost(it->first); // Check if node is in the open set
                if (open_cost < 0 || open_cost > it->second)        // if node is not in the open set or has a greater cost
                {
                    Path new_edge;                                  // Create a new edge with this destination
                    new_edge.add_node(next_src, 0.0);
                    new_edge.add_node(it->first, it->second);
                    if (open_cost < 0)                              // If not was not in the open set
                        open_set.insert(new_edge);                  // ... include its edge
                    else                                            // Or if it had a greater cost
                        open_set.chg_prioirity(new_edge);           // ... update node's edge and cost
                }
            }
        }
        if (open_set.size() > 0)                                // If there are still options in the open set
        {
            close_edge = open_set.top();                        // Take the one with least cost to insert
            open_set.pop_top();                                 // in close set, and be used in the next
            close_set.insert(close_edge);                       // iteration
            min_tree.push_back(close_edge);
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

    if (close_set.size() == base_graph.node_cnt())            // If computation ended and MST has all the graph nodes
    {                                                         // then return success
        if (debug_lvl > 1)
        {
            cout << "===========================" << endl;        
            cout << "Found Minimum Spanning Tree " << close_set; 
        }
        tree_found = true;
    }
    else
        if (debug_lvl > 0)
            cout << "No complete Spanning Tree for this graph." << endl;


    return tree_found;
}


// Return the cost of the last minimum spanning tree found
cost_type MinSpanningTree::get_cost() const
{
    cost_type tree_cost = 0.0;
    for (Path edge : this->min_tree)
        tree_cost += edge.get_cost();
    return tree_cost;
}

void MinSpanningTree::print_tree() const
{
    ios_base::fmtflags flags = cout.flags( );          // Save old output stream flags
    cout << fixed << setprecision(5);                  // Configure floating point displays    
    for (Path edge : this->min_tree)
    {
        cout << setw(4) << edge.get_source() << " ";
        cout << setw(4) << edge.get_dest() << " ";
        cout << setw(8) << edge.get_cost() << endl;
    }
    cout.flags(flags);  // Set the output flags to the way they were
}