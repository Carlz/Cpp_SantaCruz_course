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
#include "ShortestPath.h"
using namespace std;

/// \brief  Main function.
/// \param  argc    Number of command line arguments
/// \param  argv    Array of command line arguments
/// \return         Exit code, 0 upon success
///
int main(int argc, char *argv[])
{
    srand(clock());
    
    Graph null_graph;
    Graph my_graph(7);
    
    my_graph.add_edge(0,1,9);
    my_graph.add_edge(0,2,3);
    my_graph.add_edge(0,3,5);
    my_graph.add_edge(1,4,2);
    my_graph.add_edge(2,4,1);
    my_graph.add_edge(2,5,4);
    my_graph.add_edge(3,5,8);
    my_graph.add_edge(4,6,6);
    my_graph.add_edge(5,6,7);
    
    cout << "Number of Edges (null_graph): " << null_graph.edge_cnt() << endl;
    cout << "Number of Edges (my_graph): " << my_graph.edge_cnt() << endl;
    
    cout << "Number of Edges (null_graph): " << null_graph.edge_cnt() << endl;
    cout << "Number of Edges (my_graph): " << my_graph.edge_cnt() << endl;
    
    cout << null_graph;
    cout << my_graph;
    
    cout << "Size null: " << null_graph.node_cnt() << endl;
    cout << "Size my: "   << my_graph.node_cnt() << endl;

    PriorityQueue queue;    
    Path new_path({5, 3, 0}, 20.0);
    queue.insert(new_path);       
    Path path_b({5, 2, 0}, 14.0);
    queue.insert(path_b);    
    Path path_c({4, 1, 0}, 17.0);
    queue.insert(path_c);        
//    new_path.cost = 17.0;
//    new_path.dest = 6;
//    new_path.path = {4, 1, 0};
//    queue.insert(new_path);
//    new_path.cost = 10.0;
//    new_path.dest = 6;
//    new_path.path = {4, 2, 0};
//    queue.insert(new_path);
    
    cout << queue;
    
    
    if (true)
    {        
    cout << fixed << setprecision(3); 
    
    int times = 10;
    int n_edges = 0;
    for (int i = 0; i < times; ++i)
    {
        null_graph.randomize(50, 0.2);
        n_edges += null_graph.edge_cnt();
    }
    cout << "Edges mean: " << static_cast<float>(n_edges)/static_cast<float>(times) << endl;
    
    
    
    cout << "=============" << endl;
    
    cout << my_graph;
    
    ShortestPath djikstra;
    djikstra.find_path(my_graph, 0, 6);
    
    cout << "=============" << endl;
    
    null_graph.randomize(10, 0.2);    
    cout << null_graph;
    djikstra.find_path(null_graph, 0, 9);
    cout << "=============" << endl;
    }
    
    return 0;
}