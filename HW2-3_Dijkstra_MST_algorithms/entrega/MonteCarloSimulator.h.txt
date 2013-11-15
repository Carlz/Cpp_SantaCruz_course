////////////////////////////////////////////////////////////////////////////////
/// \brief      Monte Carlo Simulator for finding average shortest path in graphs
/// \author     Carlos Sampaio
/// \file       MonteCarloSimulator.h
/// \date       02/11/2013
///
///     Monte Carlo Simulator for finding average shortest path in graphs
///     using Dijkstra's shortest path algorithm.
///
////////////////////////////////////////////////////////////////////////////////

#include <iomanip>
#include "ShortestPath.h"
#include "Graph_pkg.h"
#include "Graph.h"

#ifndef MONTECARLOSIMULATOR_H
#define	MONTECARLOSIMULATOR_H

class MonteCarloSimulator {
public:
    MonteCarloSimulator() {}
   
    cost_type find_average_path(int loop_cnt, int node_cnt, float density,  // Search for average shortest path
                                cost_type min_cost, cost_type max_cost);    // in a collection of graphs
    
private:

};

#endif	/* MONTECARLOSIMULATOR_H */

