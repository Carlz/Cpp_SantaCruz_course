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
#include "Graph_pkg.h"
#include "Graph.h"
#include "Path.h"
using namespace std;

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

class PriorityQueue {
public:
    PriorityQueue(int debug_lvl = 0) : debug_lvl(debug_lvl) {}  // Simple constructor
    virtual ~PriorityQueue();             // Destructor to delete dynamically allocated Path objects.
    
    void chg_prioirity(Path& new_prio);   // changes the priority (node value) of queue element.
    void pop_top();                       // removes the top element of the queue.
    cost_type get_cost(node dest) const;  // Does the queue contain queue_element? verify with positive cost.
    void insert(Path& new_path);          // Insert a new path into queue
    Path top() const                      // Returns the top element of the queue.
        {return *(path_queue.front()); }
    int size() const                      // Return the number of queue_elements.
        {return path_queue.size(); }
    friend ostream& operator<<(ostream& out, const PriorityQueue& data); // Prints PriorityQueue structure on the screen
    
private:
    // Object used to compare paths in the queue
    class PathCompare {
    public:
        PathCompare(const bool& min_first = false) : reverse(min_first) {}   // Use min_first = true for Minimum Priority Queue
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

    vector<Path*> path_queue;       // Queue of Paths organized as a Min Heap
    vector<Path*> path_list;        // List of Paths for direct random acess
    int debug_lvl;                  // Object debug level
    
};

#endif    /* PRIORITYQUEUE_H */

