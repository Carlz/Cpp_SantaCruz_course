////////////////////////////////////////////////////////////////////////////////
/// \brief      Priority Queue class implementation
/// \author     Carlos Sampaio
/// \file       PriorityQueue.cpp
/// \date       27/10/2013
///
///     Priority Queue class implementation.
///
////////////////////////////////////////////////////////////////////////////////

#include <iomanip>
#include <algorithm>
#include <assert.h>
#include "PriorityQueue.h"

PriorityQueue::~PriorityQueue() {
    for (size_t i = 0; i < path_list.size(); ++i)
        if (path_list[i] != NULL)
            delete path_list[i];
}

// changes the priority (node value) of queue element.
void PriorityQueue::chg_prioirity(Path& new_prio)
{
    assert(new_prio.get_size() > 0);
    node dest = new_prio.get_dest();
    if (path_list[dest] != NULL)      // If destination already exists
    {
        *(path_list[dest]) = new_prio;  // Update Path and re-sort heap
        std::make_heap(path_queue.begin(), path_queue.end(), PathCompare(true));
    }
    else
        this->insert(new_prio);         // If destination doesn't exist, insert new path
    }


// removes the top element of the queue.
void PriorityQueue::pop_top()
{
    std::pop_heap(path_queue.begin(), path_queue.end(), PathCompare(true)); 
    Path* path_ptr = path_queue.back();
    path_queue.pop_back();    
    path_list[path_ptr->get_dest()] = NULL;
    delete path_ptr;
}

// does the queue contain queue_element? verify with positive cost.
float PriorityQueue::get_cost(node dest) const
{
    if (dest < path_list.size() && path_list[dest] != NULL)     // if Path exists
        return path_list[dest]->get_cost();                      // return its cost
    else                                                         // else if not exists, return negative
        return -1.0;            
}

// insert queue_element into queue
void PriorityQueue::insert(Path& new_path)
{
    assert(new_path.get_size() > 0);
    node dest = new_path.get_dest();
    if (dest >= path_list.size())    // One path for each destination
        path_list.resize(dest+1);     // Resize vector if needed
    if (path_list[dest] == NULL)     // If path doesn't exist
    {
        path_list[dest] = new Path(new_path);
        if (debug_lvl > 4)
            cout << "Added path to " << dest << " with cost: " << path_list[dest]->get_cost() << endl;
        path_queue.push_back(path_list[dest]); 
        std::push_heap(path_queue.begin(),path_queue.end(), PathCompare(true));
    }
    else
        cout << "Throw exception - path already there: " << new_path.get_source() << " to " << dest << endl;
}   


ostream& operator<<(ostream& out, const PriorityQueue& data)
{
    if (data.size() == 0)
        return (out << "Empty Priority Queue!" << endl);
    
    ios_base::fmtflags flags = out.flags( );    // Save old output stream flags
    out << fixed << setprecision(2);            // Configure floating point display

    out << "Min Path: " << data.top().get_dest() << " (" << data.top().get_cost() << ")" << endl;
    out << "Number of paths: " << data.size() << endl;
    if (data.debug_lvl > 2) 
    {
        out << "Cost\tDest\tPath  -  LIST" << endl;
        for (size_t i = 0; i < data.path_list.size(); ++i)
        {
            if (data.path_list[i] != NULL) 
            {
                out << data.path_list[i]->get_cost() << "\t" << data.path_list[i]->get_dest() << "\t";
                vector<node> node_path = data.path_list[i]->get_path();
                for (size_t j = 0; j < node_path.size(); ++j)
                    out << node_path[j] << " ";
                out << endl;
            }
            else
                out << "null" << "\t" << i << "\t" << "null" << endl;
        }
    }
    out << "Cost\tDest\tSource\tPath" << endl;
    for (vector<Path*>::const_iterator it = data.path_queue.begin(); it != data.path_queue.end(); ++it)
    {
        out << (*it)->get_cost()    << "\t";
        out << (*it)->get_dest()    << "\t";
        out << (*it)->get_source()    << "\t";
        vector<node> node_path = (*it)->get_path();
        for (size_t j = 0; j < node_path.size(); ++j)
            out << node_path[j] << " ";
        out << endl;
    }
    out << "END QUEUE\n";
    out.flags(flags);  // Set the output flags to the way they were
    return out;
}
