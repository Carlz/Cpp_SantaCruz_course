////////////////////////////////////////////////////////////////////////////////
/// \brief      C++ for C Programmers - Home Work #2.
/// \author     Carlos Sampaio
/// \file       main.cpp
/// \date       20/10/2013
///
///     The exercise objective is to implement a Monte Carlo simulation
///     that calculates the average shortest path in a collection of graphs.
///     The graph can be generated using a pseudo-random number generator
///     to produce edges and their costs.
///     The shortest path algorithm will be Dijkstra’s.
///
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "MonteCarloSimulator.h"
using namespace std;

/// \brief  Main function.
/// \param  argc    Number of command line arguments
/// \param  argv    Array of command line arguments
///         [1]     Loop count: number of Graphs to generate
///         [2]     Node count: number of nodes in the Graphs
///         [3]     Edges density
///         [4]     Minimum edge cost
///         [5]     Maximum edge cost
/// \return         Exit code, 0 upon success
///
int main(int argc, char *argv[])
{
    MonteCarloSimulator monte_carlo;
    
    srand(time(0));
    
    // Parse command line inputs
    if (argc < 4)
    {
        cout << "Arguments: <loop count> <node count> <density> [<min cost> <max cost>]" << endl;
        return 1;
    }
    int loop_cnt = atoi(argv[1]);
    int node_cnt = atoi(argv[2]);
    float density = atof(argv[3]);
    cost_type min_cost = 1.0;
    cost_type max_cost = 10.0;
    if (argc > 4)
         min_cost = atof(argv[4]);
    if (argc > 5)
         max_cost = atof(argv[5]);
    
    // Get start time - Requires C++11
    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    time_t start_time = chrono::system_clock::to_time_t(start);
    cout << endl << "started computation at " << ctime(&start_time) << endl;
    // end of C++11 requirement
    
    // Perform the Monte Carlo simulation with chosen inputs
    monte_carlo.find_average_path(loop_cnt, node_cnt, density, min_cost, max_cost);

    // Get end time - Requires C++11
    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << endl << "finished computation at " << ctime(&end_time)
         << "elapsed time: " << elapsed_seconds.count() << "s" << endl;    
    // end of C++11 requirement
    
    return 0;
}