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
#include <map>
#include "Graph.h"
using namespace std;

#ifndef PRIORITYQUEUE_H
#define	PRIORITYQUEUE_H

// Path data structure
class Path {
public:
            Path(): cost(0.0) {}
            Path(vector<node> nodes, float n_cost): node_list(nodes), cost(n_cost) {}
    node    get_source() const {return node_list.front(); }
    node    get_dest() const {return node_list.back(); }
    void    add_node(node new_node, float edge_cost) {cost += edge_cost; node_list.push_back(new_node); }
    vector<node> get_path() const {return node_list; }
    size_t  get_size() const { return node_list.size(); }
    float   get_cost() const {return cost; }
private:    
    vector<node> node_list;     // Path's nodes beginning from start node, ending by final node
    float cost;                 // Path's cost
};

class PriorityQueue {
public:
    PriorityQueue();
    PriorityQueue(const PriorityQueue& orig);
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
    vector<Path> path_list;
    
};

#endif	/* PRIORITYQUEUE_H */

