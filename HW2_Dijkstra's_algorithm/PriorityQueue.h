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
#include <deque>
#include "Graph.h"
#include "Path.h"
using namespace std;

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

class PriorityQueue {
public:
    PriorityQueue() : debug_lvl(0) {};
    virtual ~PriorityQueue();
    
    void chg_prioirity(Path& new_prio);   // changes the priority (node value) of queue element.
    void pop_top();                       // removes the top element of the queue.
    float get_cost(node dest) const;       // does the queue contain queue_element? verify with positive cost.
    void insert(Path& new_path);         // insert queue_element into queue
    Path top() const                 // returns the top element of the queue.
        {return *(path_queue.front()); }
    int size() const                      // return the number of queue_elements.
        {return path_queue.size(); }
    friend ostream& operator<<(ostream& out, const PriorityQueue& data); // Prints PriorityQueue structure on the screen    
    
private:
    class PathCompare {
    public:
        PathCompare(const bool& min_first = false) {reverse = min_first;}
        bool operator() (const Path* path_a, const Path* path_b) const
        {
            if (reverse)
                return (path_a->get_cost() > path_b->get_cost());
            else
                return (path_a->get_cost() < path_b->get_cost());
        }
    private:
        bool reverse;
    };
    
    vector<Path*> path_queue;
    deque<Path*> path_list;
    int debug_lvl;
    
};

#endif    /* PRIORITYQUEUE_H */

