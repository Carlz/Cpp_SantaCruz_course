////////////////////////////////////////////////////////////////////////////////
/// \brief      Path class implementation.
/// \author     Carlos Sampaio
/// \file       Path.cpp
/// \date       01/11/2013
///
///     Path class implementation.
///
////////////////////////////////////////////////////////////////////////////////

#include <iomanip>
#include "Path.h"

// Add node in the end of the path
void Path::add_node(node new_node, float edge_cost)
{
    cost += edge_cost;
    node_list.push_back(new_node);
}

// Prints Path structure on the screen
ostream& operator<<(ostream& out, const Path& data)
{
    ios_base::fmtflags flags = out.flags( );    // Save old output stream flags
    out << fixed << setprecision(2);            // Configure floating point displays
    
    out << "Path: ";
    for (size_t i = 0; i < data.get_path().size(); ++i)
        out << data.get_path().at(i) << " ";
    out << " -  Cost: " << data.get_cost() << endl;
    
    out.flags(flags);  // Set the output flags to the way they were
    return out;    
}


