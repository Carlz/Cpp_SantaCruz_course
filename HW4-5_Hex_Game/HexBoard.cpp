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
}

HexBoard::HexBoard(const HexBoard& orig) {
}

HexBoard::~HexBoard() {
}

char HexBoard::get_pos_token(unsigned column, unsigned line) const
{
    cost_type pos_val = bgraph.get_node_value(column + line*bsize);
    if (pos_val == RED_SPOT)
        return 'O';
    if (pos_val == BLUE_SPOT)
        return 'X';
    // Else its an Empty spot
    return '.';
}

// Prints HexBoard structure on the screen    
ostream& operator<<(ostream& out, const HexBoard& board)
{   
    // Print top line with letters for columns designation 
    out << endl << "  ";
    char column = 'A';
    for (unsigned c = 0; c < board.bsize; ++c)
        out << column++ << "   ";
    out << endl;
    
    // Print playable lines
    for (unsigned line = 0; line < board.bsize; ++line)
    {
        // Print position tokens
        out << string(2*line, ' ') << line+1 << " ";
        for (unsigned c = 0; c < board.bsize; ++c)
        {
            out << board.get_pos_token(c, line);
            if (c < board.bsize - 1)
                out << " - ";
        }
        // Blue side marker
        if ( line == board.bsize/2 - 1)
            out << "    BLUE";
        out << endl;
        
        // Print additional node links if its not the last line
        if (line < board.bsize - 1)
        {
            out << string(3+2*line, ' ');
            for (unsigned c = 0; c < board.bsize; ++c)
            {
                out << "\\ ";
                if (c < board.bsize - 1)
                    out << "/ ";
            }
        }
        out << endl;
    }
    // Red side marker
    out << string(4*board.bsize-3, ' ') << "RED";
    return out;
}

