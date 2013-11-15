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

const cost_type EMPTY_SPACE = 0.0;
const cost_type RED_SPOT    = 1.0;
const cost_type BLUE_SPOT   = 2.0;

class HexBoard {
public:
    HexBoard(unsigned size = 7);
    HexBoard(const HexBoard& orig);
    virtual ~HexBoard();
    
    // Get the character representing the occupation of a given position
    char get_pos_token(unsigned column, unsigned line) const;
    
    // Set the value representing the occupation of a given position
    void set_pos_value(unsigned column, unsigned line, cost_type val)
        { bgraph.set_node_value(column + line*bsize, val);}
    
    // Prints HexBoard structure on the screen    
    friend  ostream& operator<<(ostream& out, const HexBoard& board);
    
private:
    Graph bgraph;       // Board Graph
    unsigned bsize;     // Board Size (one dimension)

};

#endif	/* HEXBOARD_H */

