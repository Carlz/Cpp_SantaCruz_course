/* 
 * File:   HexBoard.cpp
 * Author: Capacitare
 * 
 * Created on November 15, 2013, 11:29 AM
 */

#include <cstdlib>
#include "HexBoard.h"

HexBoard::HexBoard(unsigned size)
{
    bsize = size;
    bgraph = Graph(bsize*bsize);
    const cost_type fixed_cost = 1.0;
    for (node n = 0; n < bsize*bsize; ++n)
    {
        unsigned column_index = n%bsize;
        unsigned line_index   = n/bsize;
        
        if (column_index < bsize-1)                       // if node is not in the right edge of the board
            bgraph.add_edge(n, n+1, fixed_cost);          // ... make a connection to its east neighbor

        if (line_index < bsize-1)                         // if node is not in the bottom line of the board
        {
            bgraph.add_edge(n, n+bsize, fixed_cost);      // ... make a connection to its south neighbor
            if (column_index > 0)                         // and if its not in the left edge of the board
                bgraph.add_edge(n, n+bsize-1, fixed_cost);// ... make a connection to its SW neighbor
        }
            
        bgraph.set_node_value(n, EMPTY_SPACE);            // Initialize node with empy space
    }
    
    cout << bgraph;
}

HexBoard::HexBoard(const HexBoard& orig) {
}

HexBoard::~HexBoard() {
}


// Prints HexBoard structure on the screen    
ostream& operator<<(ostream& out, const HexBoard& board)
{
    char column = 'A';
    out << endl << "  ";
    for (unsigned c = 0; c < board.bsize; ++c)
        out << itoa(column + c) << "   ";
    return out;
}

