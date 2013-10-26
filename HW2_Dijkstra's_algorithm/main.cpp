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

#include <cstdlib>
#include <iostream>
#include <vector>
#include "Graph.h"
using namespace std;

/// \brief  Main function.
/// \param  argc    Number of command line arguments
/// \param  argv    Array of command line arguments
/// \return         Exit code, 0 upon success
///
int main(int argc, char *argv[])
{
    Graph null_graph;
    Graph my_graph(10);
    
//    null_graph.add_edge(0,1,1);
    my_graph.add_edge(0,1,1);
    my_graph.add_edge(2,3,1);
    my_graph.add_edge(5,4,1);
    
    cout << "Number of Edges (null_graph): " << null_graph.edge_cnt() << endl;
    cout << "Number of Edges (my_graph): " << my_graph.edge_cnt() << endl;
    
    my_graph.delete_edge(2,3);
    
    cout << "Number of Edges (null_graph): " << null_graph.edge_cnt() << endl;
    cout << "Number of Edges (my_graph): " << my_graph.edge_cnt() << endl;

    return 0;
}