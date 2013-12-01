////////////////////////////////////////////////////////////////////////////////
/// \brief      Hex Board class implementation
/// \author     Carlos Sampaio
/// \file       HexBoard.h
/// \date       15/11/2013
///
///     Hex Board class implements a Graph to represent the playable board.
///     It controls the moves on the board.
///
////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iomanip>
#include <chrono>
#include "HexBoard.h"

//Board constructor with a variable size
HexBoard::HexBoard(unsigned size)
{
    const unsigned FIXED_COST = 1;
    bsize = size;
    bgraph = Graph<HexSpot, unsigned>(bsize*bsize + 4);  // Regular board spaces plus 4 virtual nodes for winner calculation
    free_spaces = list<PosCoord>();                      //Initialize free spaces list
    VIRTUAL_WEST  = bsize*bsize;
    VIRTUAL_EAST  = bsize*bsize + 1;
    VIRTUAL_NORTH = bsize*bsize + 2;
    VIRTUAL_SOUTH = bsize*bsize + 3;
    
    for (node n = 0; n < bsize*bsize; ++n)
    {
        unsigned column_index = n%bsize;
        unsigned line_index   = n/bsize;

        if (column_index == 0)                            // if node is in the left edge of the board
            bgraph.add_edge(n, VIRTUAL_WEST, FIXED_COST); // ... make a connection to the WEST virtual node
        
        if (column_index < bsize-1)                       // if node is not in the right edge of the board
            bgraph.add_edge(n, n+1, FIXED_COST);          // ... make a connection to its east neighbor
        
        if (column_index == bsize-1)                      // if node is in the right edge of the board
            bgraph.add_edge(n, VIRTUAL_EAST, FIXED_COST); // ... make a connection to the EAST virtual node

        if (line_index == 0)                              // if node is in the top edge of the board
            bgraph.add_edge(n, VIRTUAL_NORTH, FIXED_COST);// ... make a connection to the NORTH virtual node
        
        if (line_index < bsize-1)                         // if node is not in the bottom line of the board
        {
            bgraph.add_edge(n, n+bsize, FIXED_COST);      // ... make a connection to its south neighbor
            if (column_index > 0)                         // and if its not in the left edge of the board
                bgraph.add_edge(n, n+bsize-1, FIXED_COST);// ... make a connection to its SW neighbor
        }
        
        if (line_index == bsize-1)                        // if node is in the bottom edge of the board
            bgraph.add_edge(n, VIRTUAL_SOUTH, FIXED_COST);// ... make a connection to the SOUTH virtual node
            
        bgraph.set_node_value(n, HexSpot::EMPTY);         // Initialize node with empty space
        free_spaces.push_back(PosCoord(column_index, line_index));  // Set node into the free spaces list
    }
    // Set right colors for virtual nodes
    bgraph.set_node_value(VIRTUAL_WEST, HexSpot::BLUE);
    bgraph.set_node_value(VIRTUAL_EAST, HexSpot::BLUE);
    bgraph.set_node_value(VIRTUAL_NORTH, HexSpot::RED);
    bgraph.set_node_value(VIRTUAL_SOUTH, HexSpot::RED);
    
    // obtain a seed from the system clock for the random number generator
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    rand_generator = std::default_random_engine(seed1);
}

// Get the character representing the occupation of a given position
char HexBoard::get_pos_token(unsigned column, unsigned line) const
{
    HexSpot pos_val = this->get_pos_value(column, line);
    if (pos_val == HexSpot::BLUE)
        return 'X';
    if (pos_val == HexSpot::RED)
        return 'O';
    if (pos_val == HexSpot::WIN)
        return '@';    
    // Else its an Empty spot
    return '.';
}

// Set the value representing the occupation of a given position
bool HexBoard::set_pos_value(unsigned column, unsigned line, HexSpot val)
{
    if (this->get_pos_value(column, line) == HexSpot::EMPTY)
    {
        bgraph.set_node_value(column + line*bsize, val);
        this->fill_space(column, line);
        return true;
    }
    else
        return false;
}

// Verify if the player has completed its path, winning the game
bool HexBoard::verify_winner(HexSpot player)
{
    bool ended = false;
    if (player == BLUE)
        ended = search_algo.find_path(bgraph, VIRTUAL_WEST, VIRTUAL_EAST, player);
    else if (player == RED)
        ended = search_algo.find_path(bgraph, VIRTUAL_NORTH, VIRTUAL_SOUTH, player);
    // Check if game is ended to mark the winning path        
    if (ended)                                                  
    {
        for (node win_node : search_algo.get_path().get_path())
            bgraph.set_node_value(win_node, WIN);
    }
    return ended;
}

// Copies the players positions from a reference board
void HexBoard::copy_board(HexBoard& ref)
{
    for (node pos = 0; pos < bsize*bsize + 4; ++pos)
    {
        bgraph.set_node_value(pos, ref.bgraph.get_node_value(pos));
    }
    this->free_spaces = ref.free_spaces;
}

// Selects a random free space on the board
PosCoord HexBoard::random_free_space()
{
    std::uniform_int_distribution<int> distribution(0, free_spaces.size() - 1);
    int offset = distribution(rand_generator);
    list<PosCoord>::iterator it = free_spaces.begin();
    advance(it, offset);
    return *it;
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


//--------------------
// Private functions
//--------------------

// Mark a board hexagon as occupied
void HexBoard::fill_space(unsigned col, unsigned line)
{
    for (auto it = free_spaces.begin(); it != free_spaces.end(); ++it)
    {
        if (it->first == col && it->second == line)
        {
            free_spaces.erase(it);
            break;
        }
    }
}

