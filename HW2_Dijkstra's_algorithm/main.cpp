////////////////////////////////////////////////////////////////////////////////
/// \brief      C++ for C Programmers - Home Work #2.
/// \author     Carlos Sampaio
/// \file       main.cpp
/// \date       20/10/2013
///
///     The exercise objective is to implement a Monte Carlo simulation
///     that calculates the average shortest path in a graph.
///     The graph can be generated using a pseudo-random number generator
///     to produce edges and their costs.
///     The shortest path algorithm will be Dijkstra’s.
///
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
//#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
//#include <vector>
//#include "Graph.h"
//#include "PriorityQueue.h"
//#include "ShortestPath.h"
#include "MonteCarloSimulator.h"
using namespace std;

/// \brief  Main function.
/// \param  argc    Number of command line arguments
/// \param  argv    Array of command line arguments
/// \return         Exit code, 0 upon success
///
int main(int argc, char *argv[])
{
    MonteCarloSimulator monte_carlo;
    
//    srand(time(0));
    srand(clock());
    
    cout << endl;
    
    // Parse command line inputs
    if (argc < 4)
    {
        cout << "Arguments: <loop count> <node count> <density> [<min cost> <max cost>]" << endl;
        return 1;
    }
    int loop_cnt = atoi(argv[1]);
    int node_cnt = atoi(argv[2]);
    float density = atof(argv[3]);
    float min_cost = 1.0;
    float max_cost = 10.0;
    if (argc > 4)
         min_cost = atof(argv[4]);
    if (argc > 5)
         max_cost = atof(argv[5]);
    
    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();    
    
    monte_carlo.find_average_path(loop_cnt, node_cnt, density, min_cost, max_cost);

    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << endl << "finished computation at " << ctime(&end_time)
         << "elapsed time: " << elapsed_seconds.count() << "s" << endl;    
    
    return 0;
}