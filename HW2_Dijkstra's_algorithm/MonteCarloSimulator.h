/* 
 * File:   MonteCarloSimulator.h
 * Author: Capacitare
 *
 * Created on November 2, 2013, 3:23 PM
 */

#include <iomanip>
#include "ShortestPath.h"
#include "Graph.h"

#ifndef MONTECARLOSIMULATOR_H
#define	MONTECARLOSIMULATOR_H

class MonteCarloSimulator {
public:
    MonteCarloSimulator();
    MonteCarloSimulator(const MonteCarloSimulator& orig);
    virtual ~MonteCarloSimulator();
    
    float find_average_path(int loop_cnt, int node_cnt, float density, float min_cost, float max_cost);
    
private:

};

#endif	/* MONTECARLOSIMULATOR_H */

