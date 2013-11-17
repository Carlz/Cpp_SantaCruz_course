/* 
 * File:   HexBoard.h
 * Author: Capacitare
 *
 * Created on November 15, 2013, 11:29 AM
 */

#include "Graph.h"
using namespace std;

#ifndef HEXBOARD_H
#define	HEXBOARD_H

//const cost_type EMPTY_SPOT = 0.0;
//const cost_type BLUE_SPOT  = 1.0;
//const cost_type RED_SPOT   = 2.0;

enum HexSpot {EMPTY = 0, BLUE = 1, RED = 2};

class HexBoard {
public:
    HexBoard() {}
    HexBoard(unsigned size);
    HexBoard(const HexBoard& orig);
    virtual ~HexBoard();
    
    // Get the character representing the occupation of a given position
    char get_pos_token(unsigned column, unsigned line) const;
    
    // Set the value representing the occupation of a given position
    HexSpot get_pos_value(unsigned column, unsigned line) const
        { return bgraph.get_node_value(column + line*bsize);}
    
    // Set the value representing the occupation of a given position
    bool set_pos_value(unsigned column, unsigned line, HexSpot val);
    
    // Prints HexBoard structure on the screen    
    friend  ostream& operator<<(ostream& out, const HexBoard& board);
    
private:
    Graph<HexSpot, unsigned> bgraph;       // Board Graph
    unsigned bsize;     // Board Size (one dimension)

};

#endif	/* HEXBOARD_H */

