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

#include <cstdlib>
#include <utility>
#include <random>
#include "Graph.h"
#include "ShortestPath.h"
using namespace std;

#ifndef HEXBOARD_H
#define	HEXBOARD_H

enum HexSpot {EMPTY = 0, BLUE = 1, RED = 2, WIN = 3};
typedef pair<unsigned, unsigned> PosCoord;

class HexGame;

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
    
    // Copies the players positions from a reference board
    void copy_board(HexBoard& ref);

    // Selects a random free space on the board
    PosCoord random_free_space();
  
    friend class HexGame;
    
    // Prints HexBoard structure on the screen    
    friend  ostream& operator<<(ostream& out, const HexBoard& board);
    
private:
    unsigned bsize;                              // Board Size (one dimension)
    Graph<HexSpot, unsigned> bgraph;             // Board Graph
    ShortestPath<HexSpot, unsigned> search_algo; // Algorithm to find connection between board edges
    list<PosCoord> free_spaces;                  // Empty spaces on the board, in board graph index values
    std::default_random_engine rand_generator;   // C++11 Random number generator
    
    // Virtual nodes for winner calculation
    node VIRTUAL_WEST;
    node VIRTUAL_EAST;
    node VIRTUAL_NORTH;
    node VIRTUAL_SOUTH;
    
    void fill_space(unsigned col, unsigned line);   // Mark a board hexagon as occupied    
};

#endif	/* HEXBOARD_H */

