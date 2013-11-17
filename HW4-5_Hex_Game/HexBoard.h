////////////////////////////////////////////////////////////////////////////////
/// \brief      Hex Board class definition
/// \author     Carlos Sampaio
/// \file       HexBoard.h
/// \date       15/11/2013
///
///     Hex Board class implements a Graph to represent the playable board.
///     It controls the moves on the board.
///
////////////////////////////////////////////////////////////////////////////////

#include "Graph.h"
#include "ShortestPath.h"
using namespace std;

#ifndef HEXBOARD_H
#define	HEXBOARD_H

enum HexSpot {EMPTY = 0, BLUE = 1, RED = 2};

class HexBoard {
public:
    HexBoard() {}
    HexBoard(unsigned size);           //Board constructor with a variable size
    HexBoard(const HexBoard& orig) {}
    virtual ~HexBoard() {}
    
    // Get the character representing the occupation of a given position
    char get_pos_token(unsigned column, unsigned line) const;
    
    // Set the value representing the occupation of a given position
    HexSpot get_pos_value(unsigned column, unsigned line) const
        { return bgraph.get_node_value(column + line*bsize);}
    
    // Set the value representing the occupation of a given position
    bool set_pos_value(unsigned column, unsigned line, HexSpot val);
    
    // Verify if the player has completed its path, winning the game
    bool verify_winner(HexSpot player);
    
    // Prints HexBoard structure on the screen    
    friend  ostream& operator<<(ostream& out, const HexBoard& board);
    
private:
    unsigned bsize;                              // Board Size (one dimension)
    Graph<HexSpot, unsigned> bgraph;             // Board Graph
    ShortestPath<HexSpot, unsigned> search_algo; // Algorithm to find connection between board edges
    
    // Virtual nodes for winner calculation
    node VIRTUAL_WEST;
    node VIRTUAL_EAST;
    node VIRTUAL_NORTH;
    node VIRTUAL_SOUTH;
};

#endif	/* HEXBOARD_H */

