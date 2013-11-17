////////////////////////////////////////////////////////////////////////////////
/// \brief      Hex Game main
/// \author     Carlos Sampaio
/// \file       main.cpp
/// \date       15/11/2013
///
///     Hex Game implementation. http://en.wikipedia.org/wiki/Hex_%28board_game%29
///     Currently supports only 2 human players.
///
////////////////////////////////////////////////////////////////////////////////

#include "HexGame.h"
using namespace std;

// Implements the flow control of the game
int main(int argc, char** argv) {
    
    HexGame game;               // Game control
    HexSpot player;             // Current player
    unsigned move;              // Current move
    
    game.greetings();           // Print greetings message
    for (;;)                    // Loop for various matches
    {
        player = BLUE;          // Start with BLUE player
        move = 0;
        game.start_game();      // Get the number of players and board size
        for (;;)                // Loop for various moves
        {
            if (move == 0)      // Print Move number
            {
                cout << "No moves" << endl;
                move++;
            }
            else
            {
                cout << endl << "After move " << move++ << endl;
            }
            game.print_board();                 // Print current board
            if (game.get_human_play(player))    // Get human play and check if game is ended
                break;
            if (player == BLUE)                 // Change players
                player = RED;
            else
                player = BLUE;
        }
        cout << endl << "After move " << move << endl;   // When game has ended, print the winner
        game.print_board();
        cout << "> The " << game.get_player_name(player) << " player won! Congratulations!" << endl;
        if (!game.play_again())                          // Check if one wants to play it again
            break;
    }
    
    return 0;
}

