/* 
 * File:   Path.cpp
 * Author: Capacitare
 * 
 * Created on November 1, 2013, 10:54 PM
 */

#include <iomanip>
#include "Path.h"

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


