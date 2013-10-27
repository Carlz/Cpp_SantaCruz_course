////////////////////////////////////////////////////////////////////////////////
/// \brief      Priority Queue class definition.
/// \author     Carlos Sampaio
/// \file       PriorityQueue.h
/// \date       27/10/2013
///
///     Priority Queue class definition.
///
////////////////////////////////////////////////////////////////////////////////


#include <vector>
#include <queue>        // for std::priority_queue
#include "Graph.h"
using namespace std;

#ifndef PRIORITYQUEUE_H
#define	PRIORITYQUEUE_H


// Path data structure
struct path_data {
    node dest;                  // Path's destination
    vector<node> path;          // Path's nodes, source last
    float cost;                 // Path's cost
};


class PathCompare {
public:
    PathCompare(const bool& min_first = false) {reverse = min_first;}
    bool operator() (const path_data& path_a, const path_data& path_b) const
    {
        if (reverse)
            return (path_a.cost > path_b.cost);
        else
            return (path_a.cost < path_b.cost);
    }
private:
    bool reverse;
};


class PriorityQueue {
public:
    PriorityQueue();
    PriorityQueue(const PriorityQueue& orig);
    virtual ~PriorityQueue();
    
    void chg_prioirity(path_data& new_prio);   // changes the priority (node value) of queue element.
    void pop_top();                       // removes the top element of the queue.
    bool contains(node dest) const;       // does the queue contain queue_element.
    void insert(path_data& path);         // insert queue_element into queue
    path_data top() const                 // returns the top element of the queue.
        {return path_queue.front(); }
    int size() const                      // return the number of queue_elements.
        {return path_queue.size(); }
    friend ostream& operator<<(ostream& out, const PriorityQueue& data); // Prints PriorityQueue structure on the screen    
    
private:
    vector<path_data> path_queue;
    
};

#endif	/* PRIORITYQUEUE_H */

