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
    bool updated = false;
    for (int i = 0; i < path_queue.size(); ++i)
        if (path_queue[i].get_dest() == new_prio.get_dest())
        {
            path_queue[i] = new_prio;
            updated = true;
        }
    if (updated)
        std::sort_heap(path_queue.begin(), path_queue.end(), PathCompare(true));
}


// removes the top element of the queue.
void PriorityQueue::pop_top()
{
    std::pop_heap(path_queue.begin(), path_queue.end(), PathCompare(true)); 
    path_queue.pop_back();
}

// does the queue contain queue_element.
bool PriorityQueue::contains(node dest) const
{
    for (int i = 0; i < path_queue.size(); ++i)
        if (path_queue[i].get_dest() == dest)
            return true;
    // If not found return false
    return false;            
}

// insert queue_element into queue
void PriorityQueue::insert(Path& new_path)
{
    path_queue.push_back(new_path); 
    std::push_heap(path_queue.begin(),path_queue.end(), PathCompare(true));
}   


ostream& operator<<(ostream& out, const PriorityQueue& data)
{
    if (data.size() == 0)
        return (out << "Empty Priority Queue!" << endl);
    
    ios_base::fmtflags flags = out.flags( );    // Save old output stream flags
    out << fixed << setprecision(2);            // Configure floating point display

    out << "Min Path: " << data.top().get_dest() << " (" << data.top().get_cost() << ")" << endl;
    out << "Number of paths: " << data.size() << endl;
    out << "Cost\tDest\tPath" << endl;
    for (auto it = data.path_queue.begin(); it != data.path_queue.end(); ++it)
    {
        out << it->get_cost() << "\t" << it->get_dest() << "\t";
        vector<node> node_path = it->get_path();
        for (int j = 0; j < node_path.size(); ++j)
            out << node_path[j] << " ";
        out << endl;
    }
    out.flags(flags);  // Set the output flags to the way they were
    return out;
}
