/* 
 * File:   HexBoard.cpp
 * Author: Capacitare
 * 
 * Created on November 15, 2013, 11:29 AM
 */

#include <cstdlib>
#include <iomanip>
#include "HexBoard.h"

HexBoard::HexBoard(unsigned size)
{
    bsize = size;
    bgraph = Graph<HexSpot, unsigned>(bsize*bsize);
    const unsigned fixed_cost = 1;
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
            
        bgraph.set_node_value(n, HexSpot::EMPTY);                  // Initialize node with empty space
    }
}

HexBoard::HexBoard(const HexBoard& orig) {
}

HexBoard::~HexBoard() {
}

char HexBoard::get_pos_token(unsigned column, unsigned line) const
{
    HexSpot pos_val = this->get_pos_value(column, line);
    if (pos_val == HexSpot::BLUE)
        return 'X';
    if (pos_val == HexSpot::RED)
        return 'O';
    // Else its an Empty spot
    return '.';
}

// Set the value representing the occupation of a given position
bool HexBoard::set_pos_value(unsigned column, unsigned line, HexSpot val)
{
    if (this->get_pos_value(column, line) == HexSpot::EMPTY)
    {
        bgraph.set_node_value(column + line*bsize, val);
        return true;
    }
    else
        return false;
}

// Prints HexBoard structure on the screen    
ostream& operator<<(ostream& out, const HexBoard& board)
{   
    // Red side marker
    out << endl << string(2*board.bsize-2, ' ') << "RED (O)" << endl << endl;    
    // Print top line with letters for columns designation 
    out << "   ";
    char column = 'A';
    for (unsigned c = 0; c < board.bsize; ++c)
        out << column++ << "   ";
    out << endl << endl;
    
    // Print playable lines
    for (unsigned line = 0; line < board.bsize; ++line)
    {
        // Blue side marker in the middle line
        if ( line == board.bsize/2 && line >= 5)
            out << string(2*line - 9, ' ')<< "BLUE (X) ";
        else
            out << string(2*line, ' ');
        // Print position tokens
        out << setw(2) << right << line+1 << "  ";
        for (unsigned c = 0; c < board.bsize; ++c)
        {
            out << board.get_pos_token(c, line);
            if (c < board.bsize - 1)
                out << " - ";
        }
        out << "  " << line+1;
        // Blue side marker in the middle line
        if ( line == board.bsize/2 - 1)
            out << "  BLUE (X)";
        out << endl;
        
        // Print additional node links if its not the last line
        if (line < board.bsize - 1)
        {
            out << string(5+2*line, ' ');
            for (unsigned c = 0; c < board.bsize; ++c)
            {
                out << "\\ ";
                if (c < board.bsize - 1)
                    out << "/ ";
            }
        }
        out << endl;
    }
    // Print bottom line with letters for columns designation 
    out << string(3+2*board.bsize, ' ');
    column = 'A';
    for (unsigned c = 0; c < board.bsize; ++c)
        out << column++ << "   ";
    out << endl << endl;
    // Red side marker
    out << string(4*board.bsize-2, ' ') << "RED (O)" << endl << endl;
    
    return out;
}

