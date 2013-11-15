////////////////////////////////////////////////////////////////////////////////
/// \brief      C++ for C Programmers - Home Work #3.
/// \author     Carlos Sampaio
/// \file       main_mst.cpp
/// \date       20/10/2013
///
///     The exercise objective is to implement a Minimum Spanning Tree algorithm
///     for a weighted undirected graph that should be read from a file with
///     a given format.
///     This implementation utilizes Prim’s algorithm.
///     The input graph file is given by a command line argument
///     and the outputs are printed on the screen: MST edges and cost.
///
////////////////////////////////////////////////////////////////////////////////

#define  NDEBUG     //disables assertions for performance

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <chrono>
#include "Graph.h"
#include "PriorityQueue.h"
#include "MinSpanningTree.h"
using namespace std;

/// \brief  Main function.
/// \param  argc    Number of command line arguments
/// \param  argv    Array of command line arguments
///         [1]     Graph file: path for input file with graph description
///         [2]     Debug level: set program verbosity (-1 to 10)
/// \return         Exit code, 0 upon success
///
int main(int argc, char *argv[])
{
    // Process inputs
    string in_file;
    int debug_lvl = 0;
    if (argc > 1)
        in_file = string(argv[1]);
    else
    {
        cout << "Arguments: <file_name> [<debug_lvl>]" << endl;
        return 1;
    }
    if (argc > 2)
        debug_lvl = atoi(argv[2]);
    
    // Get start time for build graph
    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    time_t start_time = chrono::system_clock::to_time_t(start);
    cout << endl << "started computation at " << ctime(&start_time);
    
    // Read and build Graph
    Graph ld_graph(in_file);
    
    // Get end time for build graph
    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cout << endl << "finished building graph after " 
         << elapsed_seconds.count() << "s" << endl << endl;

    // Check if graph was created correctly
    if (ld_graph.node_cnt() == 0)
    {
        cout << "Empty graph!" << endl;
        return 1;
    }
    
    // Get start time for MST search
    start = chrono::system_clock::now();
    
    if (debug_lvl > 0)
            cout << ld_graph;

    // Calculate MST
    MinSpanningTree mst_algo(debug_lvl);
    bool mst_found = mst_algo.find_prim_tree(ld_graph);

    // Get end time for MST search
    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "finished calculating MST after "
         << elapsed_seconds.count() << "s" << endl << endl;
        
    // Report results
    if (mst_found)
    {
        if (debug_lvl > -1)
        {
            cout << "Minimum Spanning Tree:" << endl;
            mst_algo.print_tree();
            cout << endl;
        }
        cout << fixed << setprecision(5);
        cout << "Total MST cost: " << mst_algo.get_cost();
    }
    else
        cout << "No complete Spanning Tree for this graph.";
    
    return 0;
}