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
#include <chrono>
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
int main_(int argc, char *argv[])
{
    srand(time(0));
    
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

    if (true)
    {        
        cout << "Number of Edges (null_graph): " << null_graph.edge_cnt() << endl;
        cout << "Number of Edges (my_graph): " << my_graph.edge_cnt() << endl;

        cout << "Number of Edges (null_graph): " << null_graph.edge_cnt() << endl;
        cout << "Number of Edges (my_graph): " << my_graph.edge_cnt() << endl;

        cout << null_graph;
        cout << my_graph;

        cout << "Size null: " << null_graph.node_cnt() << endl;
        cout << "Size my: "   << my_graph.node_cnt() << endl;

        PriorityQueue queue(5);    

        vector<node> vec(3);
        vec[0] = 5; vec[1] = 3; vec[2] = 0;
        Path new_path(vec, 20.0);
        queue.insert(new_path);       
        vec[0] = 5; vec[2] = 3; vec[2] = 0;
        Path path_b(vec, 14.0);
        queue.insert(path_b);    
        cout << queue;	

        vec[0] = 0; vec[1] = 2; vec[2] = 4;
        Path path_c(vec, 17.0);
        queue.insert(path_c);        
        vec[0] = 1; vec[1] = 3; vec[2] = 5;
        Path path_d(vec, 15.0);
        queue.insert(path_d);
        cout << queue;	
	}
    
    if (false)
    {        
        cout << fixed << setprecision(3); 

        int times = 100;
        int n_edges = 0;
        for (int i = 0; i < times; ++i)
        {
            null_graph.randomize(50, 0.4);
            n_edges += null_graph.edge_cnt();
        }
        cout << "Edges mean: " << static_cast<float>(n_edges)/static_cast<float>(times) << endl;
        
        cout << "=============" << endl;        
    }

    ShortestPath dijkstra(1);    
    
    if (true)
    {       
        cout << my_graph;

        if (dijkstra.find_path(my_graph, 0, 6))
//            cout << dijkstra.get_path() << endl;
//        else
//            cout << "No shortest path" << endl;

        cout << "=============" << endl;
    }
    
    if (true)
    {     
        null_graph.randomize(50, 1);    
        cout << null_graph;
        for (int i = 1; i < 50; ++i)
        {
            if (dijkstra.find_path(null_graph, 0, i))
            {
                cout << dijkstra.get_path() << endl;
            }
            else
                cout << "No shortest path" << endl;
        }
    //    if (dijkstra.find_path(null_graph, 0, 8))
    //        cout << dijkstra.get_path() << endl;
    //    else
    //        cout << "No shortest path" << endl;
        cout << "=============" << endl;
    }
    
    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();

    if (false)
    {
        int loop_max = atoi(argv[1]);
        float density = atof(argv[2]);
        int node_cnt = 50;
        float mean_cost = 0.0;
        float average_size = 0.0;
        int acc_edge = 0;
        for (int loop = 0; loop < loop_max; ++loop)
        {   
            int found_n = 0;
            float accum = 0.0;
            int acc_size = 0;
            null_graph.randomize(node_cnt, density);
            for (node dest = 1; dest < node_cnt; ++dest)
                if (dijkstra.find_path(null_graph, 0, dest))
                {
                    accum += dijkstra.get_path().get_cost();
                    acc_size += dijkstra.get_size() - 1 ;
                    ++found_n;
                }
            mean_cost += accum/static_cast<float>(found_n);
            average_size += static_cast<float>(acc_size)/static_cast<float>(found_n);
            acc_edge += null_graph.edge_cnt();
        }
        cout << fixed << setprecision(2);
        cout << "Edges: " << static_cast<float>(acc_edge)/loop_max << endl;
        float result = mean_cost/static_cast<float>(loop_max);
        float result_size = average_size/static_cast<float>(loop_max);
        cout << "Density: " << density << " Cost: " << result << " Length: " << result_size << endl;
    }
    
    end = chrono::system_clock::now();
 
    chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);
 
    cout << "finished computation at " << ctime(&end_time)
         << "elapsed time: " << elapsed_seconds.count() << "s\n";    
    
    return 0;
}