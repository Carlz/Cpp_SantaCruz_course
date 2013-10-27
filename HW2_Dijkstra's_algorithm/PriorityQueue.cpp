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
#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() {
}

PriorityQueue::PriorityQueue(const PriorityQueue& orig) {
}

PriorityQueue::~PriorityQueue() {
}

// changes the priority (node value) of queue element.
void PriorityQueue::chg_prioirity(path_data& new_prio)
{
    bool updated = false;
    for (int i = 0; i < path_queue.size(); ++i)
        if (path_queue[i].dest == new_prio.dest)
        {
            path_queue[i].cost = new_prio.cost;
            path_queue[i].path = new_prio.path;
            updated = true;
        }
    if (updated)
        std::sort_heap(path_queue.begin(), path_queue.end(), PathCompare(true));
}


// removes the top element of the queue.
void PriorityQueue::pop_top()
{
    pop_heap(path_queue.begin(), path_queue.end(), PathCompare(true)); 
    path_queue.pop_back();
}

// does the queue contain queue_element.
bool PriorityQueue::contains(node dest) const
{
    for (int i = 0; i < path_queue.size(); ++i)
        if (path_queue[i].dest == dest)
            return true;
    // If not found return false
    return false;            
}

// insert queue_element into queue
void PriorityQueue::insert(path_data& path)
{
    path_queue.push_back(path); 
    push_heap(path_queue.begin(),path_queue.end(), PathCompare(true));
}   


ostream& operator<<(ostream& out, const PriorityQueue& data)
{
    if (data.size() == 0)
        return (out << "Empty Priority Queue!" << endl);
    
    ios_base::fmtflags flags = out.flags( );    // Save old output stream flags
    out << fixed << setprecision(2);            // Configure floating point display

    out << "Number of paths: " << data.size() << endl;
    out << "Cost\tDest\tPath" << endl;
    for (auto it = data.path_queue.begin(); it != data.path_queue.end(); ++it)
    {
        out << it->cost << "\t" << it->dest << "\t";
        for (auto path = it->path.begin(); path != it->path.end(); ++path)
            out << *path << " ";
        out << endl;
    }
    out.flags(flags);  // Set the output flags to the way they were
    return out;
}
