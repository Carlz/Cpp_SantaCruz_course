////////////////////////////////////////////////////////////////////////////////
/// \brief      Priority Queue class implementation
/// \author     Carlos Sampaio
/// \file       PriorityQueue.h
/// \date       27/10/2013
///
///     Priority Queue class implementation.
///
////////////////////////////////////////////////////////////////////////////////

#include <iomanip>
#include <algorithm>
#include <assert.h>
#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() {
}

PriorityQueue::PriorityQueue(const PriorityQueue& orig) {
}

PriorityQueue::~PriorityQueue() {
}

// changes the priority (node value) of queue element.
void PriorityQueue::chg_prioirity(Path& new_prio)
{
    assert(new_prio.get_size() > 0);
    node dest = new_prio.get_dest();
    if (this->get_cost(dest) >= 0)      // If destination already exists
    {
        path_list[dest] = new_prio;     // Update Path and re-sort heap
        std::sort_heap(path_queue.begin(), path_queue.end(), PathCompare(true));
    }
    else
        this->insert(new_prio);         // If destination doesn't exist, insert new path
}


// removes the top element of the queue.
void PriorityQueue::pop_top()
{
    std::pop_heap(path_queue.begin(), path_queue.end(), PathCompare(true)); 
    path_queue.pop_back();
}

// does the queue contain queue_element? verify with positive cost.
float PriorityQueue::get_cost(node dest) const
{
    if (dest < path_list.size() && path_list[dest].get_size() > 0)             // if Path exists
    {
        cout << path_list[dest].get_size() << endl;
        return path_list[dest].get_cost();        // return its cost
    }
    else                                             // else if not exists, return negative
        return -1.0;            
}

// insert queue_element into queue
void PriorityQueue::insert(Path& new_path)
{
    assert(new_path.get_size() > 0);
    node dest = new_path.get_dest();
    if (dest >= path_list.size())    // One path for each destination
        path_list.resize(dest+1);     // Resize vector if needed
   cout << "cost:" <<path_list[dest].get_cost() << endl;
    if (path_list[dest].get_size() == 0)     // If path doesn't exist
    {
        path_list[dest] = new_path;
        path_queue.push_back(&(path_list[dest])); 
        std::push_heap(path_queue.begin(),path_queue.end(), PathCompare(true));
    }
    else
        cout << "Trow exception - path already there" << endl;
}   


ostream& operator<<(ostream& out, const PriorityQueue& data)
{
    if (data.size() == 0)
        return (out << "Empty Priority Queue!" << endl);
    
    ios_base::fmtflags flags = out.flags( );    // Save old output stream flags
    out << fixed << setprecision(2);            // Configure floating point display

    out << "Min Path: " << data.top().get_dest() << " (" << data.top().get_cost() << ")" << endl;
    out << "Number of paths: " << data.size() << endl;
    out << "Cost\tDest\tPath  -  LIST" << endl;
    for (size_t i = 0; i < data.path_list.size(); ++ i)
    {
        out << data.path_list[i].get_cost() << "\t" << data.path_list[i].get_dest() << "\t";
        vector<node> node_path = data.path_list[i].get_path();
        for (size_t j = 0; j < node_path.size(); ++j)
            out << node_path[j] << " ";
        out << endl;        
        
    }
    out << "Cost\tDest\tPath  -  QUEUE" << endl;
    for (vector<Path*>::const_iterator it = data.path_queue.begin(); it != data.path_queue.end(); ++it)
    {
        out << (*it)->get_cost() << "\t" << (*it)->get_dest() << "\t";
        vector<node> node_path = (*it)->get_path();
        for (size_t j = 0; j < node_path.size(); ++j)
            out << node_path[j] << " ";
        out << endl;
    }
    out.flags(flags);  // Set the output flags to the way they were
    return out;
}
