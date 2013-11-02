////////////////////////////////////////////////////////////////////////////////
/// \brief      Priority Queue class implementation
/// \author     Carlos Sampaio
/// \file       MonteCarloSimulator.cpp
/// \date       02/11/2013
///
///     Priority Queue class implementation.
///
////////////////////////////////////////////////////////////////////////////////

#include "MonteCarloSimulator.h"

/// \brief  Main function.
/// \param  argc    Number of command line arguments
/// \param  argv    Array of command line arguments
/// \return         
///
float MonteCarloSimulator::find_average_path(int loop_cnt, int node_cnt, float density,
                                             float min_cost, float max_cost) 
{
    double global_acc_cost = 0.0;       // accumulate number of paths cost in all graphs
    double global_acc_size = 0.0;       // accumulate number of paths edge count in all graphs
    int    global_acc_edge = 0;         // accumulate number of edges in all graphs
    
    cout << "loops: " << loop_cnt << "  nodes: " << node_cnt << "  density: " << density
         << "  cost: [" << min_cost << "," << max_cost << ")" << endl;
    
    // Iterate over requested number repetitions
    for (int loop = 0; loop < loop_cnt; ++loop)
    {   
        int found_n = 0;                // number of paths found in this graph
        float acc_cost = 0.0;           // accumulate number of paths cost in this graph
        int acc_size = 0;               // accumulate number of paths edge count in this graph
        
        Graph search_graph;             // Random Graph object to look for paths 
        search_graph.randomize(node_cnt, density, min_cost, max_cost);
        
        ShortestPath dijkstra(0);   // debug level
        
        // Search for paths from node 0 to N-1
        for (node dest = 1; dest < node_cnt; ++dest)
            if (dijkstra.find_path(search_graph, 0, dest))
            {
                acc_cost += dijkstra.get_path().get_cost();     // Save results if path was found
                acc_size += dijkstra.get_size() - 1 ;
                ++found_n;
            }
        
        // Include this Graph instance results in global Monte Carlo data
        global_acc_cost += acc_cost/found_n;
        global_acc_size += static_cast<float>(acc_size)/found_n;
        global_acc_edge += search_graph.edge_cnt();
    }

    float average_cost  = global_acc_cost/loop_cnt;
    float average_size  = global_acc_size/loop_cnt;
    float average_edges = static_cast<float>(global_acc_edge)/loop_cnt;    
    
    ios_base::fmtflags flags = cout.flags( );    // Save old output stream flags
    cout << fixed << setprecision(2);            // Configure floating point display
    
    cout << "average path cost:\t" << average_cost << endl
         << "average path edges:\t" << average_size << endl
         << "average graph edges:\t" << average_edges << endl;

    cout.flags(flags);                           // Set the output flags to the way they were
    
    return average_cost;
}
