////////////////////////////////////////////////////////////////////////////////
/// \brief      Hex Game main - Home Work #4
/// \author     Carlos Sampaio
/// \file       main.cpp
/// \date       15/11/2013
///
///     Hex Game implementation. http://en.wikipedia.org/wiki/Hex_%28board_game%29
///     Currently supports only 2 human players.
///     The end of game verification is done by checking the existence of a path
///     between two virtual nodes connected to the edges of the board. This is
///     done using Djikstra's algorithm.
///
////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <ctime>
#include "HexGame.h"
using namespace std;

// Implements the flow control of the game
int main(int argc, char** argv) {
    
    unsigned trials = 1000;
    if (argc > 1)
        trials = atoi(argv[1]);

    HexGame game(trials);       // Game control
    HexSpot player;             // Current player
    unsigned move;              // Current move
    
    srand(time(0));
    
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
            if (game.get_next_move(player))     // Get next move and check if game is ended
                break;                          // Break if game is over
            player = (player == BLUE ? RED : BLUE);
        }
        cout << endl << "After move " << move << endl;   // When game has ended, print the winner
        game.print_board();
        cout << "> " << game.get_player_name(player) << " player wins! Congratulations! The winning path is marked with: @" << endl;
        if (!game.play_again())                          // Check if one wants to play it again
            break;
    }
    
    return 0;
}

