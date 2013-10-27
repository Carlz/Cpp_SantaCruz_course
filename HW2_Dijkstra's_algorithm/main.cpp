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
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Graph.h"
#include "PriorityQueue.h"
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
    
    srand(clock());
    
//    null_graph.add_edge(0,1,1);
    my_graph.add_edge(0,1,1);
    my_graph.add_edge(2,3,1);
    my_graph.add_edge(5,4,1);
    
    cout << "Number of Edges (null_graph): " << null_graph.edge_cnt() << endl;
    cout << "Number of Edges (my_graph): " << my_graph.edge_cnt() << endl;
    
    my_graph.delete_edge(2,3);
    
    cout << "Number of Edges (null_graph): " << null_graph.edge_cnt() << endl;
    cout << "Number of Edges (my_graph): " << my_graph.edge_cnt() << endl;
    
    cout << null_graph;
    cout << my_graph;
    
    cout << "Size null: " << null_graph.node_cnt() << endl;
    cout << "Size my: "   << my_graph.node_cnt() << endl;
    
    null_graph.randomize(5, 0.5);    
    cout << null_graph;

    PriorityQueue queue;    
    path_data new_path;
    new_path.cost = 20.0;
    new_path.dest = 6;
    new_path.path = {5, 3, 0};
    queue.insert(new_path);       
    new_path.cost = 14.0;
    new_path.dest = 6;
    new_path.path = {5, 2, 0};
    queue.insert(new_path);    
    new_path.cost = 17.0;
    new_path.dest = 6;
    new_path.path = {4, 1, 0};
    queue.insert(new_path);
    new_path.cost = 10.0;
    new_path.dest = 6;
    new_path.path = {4, 2, 0};
    queue.insert(new_path);
    
    cout << queue;
    
    
    
    cout << fixed << setprecision(3); 
    
    int times = 1;
    int n_edges = 0;
    for (int i = 0; i < times; ++i)
    {
        null_graph.randomize(50, 0.2);
        n_edges += null_graph.edge_cnt();
    }
    cout << "Edges mean: " << static_cast<float>(n_edges)/static_cast<float>(times) << endl;
    return 0;
}