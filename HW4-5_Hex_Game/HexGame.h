////////////////////////////////////////////////////////////////////////////////
/// \brief      Hex Game class definition
/// \author     Carlos Sampaio
/// \file       HexGame.h
/// \date       16/11/2013
///
///     Hex Game class implements the control structures for the game play.
///
////////////////////////////////////////////////////////////////////////////////

#include "HexBoard.h"
using namespace std;

#ifndef HEXGAME_H
#define	HEXGAME_H

class HexGame {
public:
    HexGame() {}
    HexGame(const HexGame& orig) {}
    virtual ~HexGame() {}
    
    // Print Hex Game greetings message
    void greetings()
        { cout << "Welcome to Hex Game v" << HEX_VERSION_MAJOR << "." << HEX_VERSION_MINOR << " !" << endl;}
    
    // Get user inputs to initialize the game board and start the game
    void start_game();
    
    // Print the Hex Board on the Screen
    void print_board()
        { cout << board;}
    
    // Get the user play input and checks for a winner, if game has ended return true, else false.
    bool get_human_play(HexSpot color);
    
    // Return player name
    string get_player_name(HexSpot color)
        { return PLAYER_LABEL[color];}
    
    // Get the user input if a new game should be started 
    bool play_again();
    
private:
    const unsigned HEX_VERSION_MAJOR = 1;     // Game major version
    const unsigned HEX_VERSION_MINOR = 0;     // Game minor version
    const vector<string> PLAYER_LABEL = {"NONE", "BLUE", "RED"}; // Player names
    HexBoard board;                           // Board object
    unsigned board_size;                      // Size of one dimension of the board
    unsigned human_player;                    // Number of human players

};

#endif	/* HEXGAME_H */

