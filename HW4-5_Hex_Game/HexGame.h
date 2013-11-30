////////////////////////////////////////////////////////////////////////////////
/// \brief      Hex Game class definition
/// \author     Carlos Sampaio
/// \file       HexGame.h
/// \date       16/11/2013
///
///     Hex Game class implements the control structures for the game play.
///
////////////////////////////////////////////////////////////////////////////////

#include <list>
#include <vector>
#include <utility>
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
    
    // Get next player move
    bool get_next_move(HexSpot color);
    
    // Get the user play input and checks for a winner, if game has ended return true, else false.
    bool get_human_play(HexSpot color);
    
    // Calculate the next computer play
    bool get_computer_play(HexSpot color);
    
    // Return player name
    string get_player_name(HexSpot color)
        { return PLAYER_LABEL[color];}
    
    // Get the user input if a new game should be started 
    bool play_again();
    
private:
    const unsigned HEX_VERSION_MAJOR = 1;     // Game major version
    const unsigned HEX_VERSION_MINOR = 1;     // Game minor version
    const unsigned MC_TRIALS = 500;    
    const vector<string> PLAYER_LABEL = {"NONE", "BLUE", "RED"}; // Player names
    enum HexPlayer { HUMAN, COMPUTER };
    HexBoard board;                           // Board object
    HexBoard aux_board;                       // Auxiliary board to calculate computer plays
    unsigned board_size;                      // Size of one dimension of the board
    vector<HexPlayer> players;
    
    // Get the user input for a yes or no question
    bool make_yn_question(string question);
    
};

#endif	/* HEXGAME_H */

