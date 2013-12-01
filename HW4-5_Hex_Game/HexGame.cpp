////////////////////////////////////////////////////////////////////////////////
/// \brief      Hex Game class implementation
/// \author     Carlos Sampaio
/// \file       HexGame.cpp
/// \date       16/11/2013
///
///     Hex Game class implements the control structures for the game play.
///     Based on http://en.wikipedia.org/wiki/Hex_%28board_game%29
///
////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <limits>
#include "HexGame.h"


// Print Hex Game greetings message
void HexGame::greetings()
{
    cout << "Welcome to Hex Game v" << HEX_VERSION_MAJOR << "." << HEX_VERSION_MINOR << " !" << endl << endl
         << "This game is based on a 2 players board game called Hex. Each player has an allocated color, BLUE (X) and RED (O)." << endl
         << "Players take turns placing a stone of their color on a single free spot (.) within the overall playing board." << endl
         << "The goal for each player is to form a connected path of their own stones linking the opposing sides of the board" << endl
         << "marked by their colors. The first player to complete his or her connection wins the game." << endl
         << "A valid path is formed by stones connected by the dashes on the board and do not need to be a straight line." << endl << endl
         << "The BLUE (X) player connects from EAST to WEST and plays first, while the RED (O) player connects from NORTH to SOUTH." << endl;

}

// Get user inputs to initialize the game board and start the game
void HexGame::start_game()
{
    unsigned nplayer, bsize;
    
    // Get the number of players input 
    for (;;)
    {
        cout << endl << "Enter the number of human players (0,1,2): ";
        if (cin >> nplayer) 
        {
            if ((nplayer >= 0) && (nplayer <= 2))
                break;  // valid value
            else
                cout << "Invalid number of human players: " << nplayer << endl;
        }
        else
        {
            cout << "Please enter a valid integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cout << endl << "Number of human players: " << nplayer << endl;
    cout << "Number of computer players: " << 2 - nplayer << endl;
    
    // Define players and their order
    players = vector<HexPlayer>(3);
    switch (nplayer)
    {
        case 0:
            players[BLUE] = COMPUTER;
            players[RED] = COMPUTER;
            break;
        case 1:
            if (make_yn_question("Do you want to be the BLUE player and play first (Y or N)? "))
            {
                players[BLUE] = HUMAN;
                players[RED] = COMPUTER;
            }
            else
            {
                players[BLUE] = COMPUTER;
                players[RED] = HUMAN;
            }
            break;
        default:
            players[BLUE] = HUMAN;
            players[RED] = HUMAN;
            break;            
    }
    
    // Get the board size input
    for (;;)
    {
        cout << endl << "Enter the board size (2 to 26): ";
        if (cin >> bsize) 
        {
            if ((bsize >= 2) && (bsize <= 26))
                break;  // valid value
            else
                cout << "Invalid board size: " << bsize << endl;
        }
        else
        {
            cout << "Please enter a valid integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cout << endl;
    board = HexBoard(bsize);
    aux_board = HexBoard(bsize);
    board_size = bsize;
}

// Get the user play input and checks for a winner, if game has ended return true, else false.
bool HexGame::get_human_play(HexSpot color)
{
    char column;
    unsigned col_index, line;
    
    for (;;)
    {
        cout << endl << "> " << PLAYER_LABEL.at(color) << " player (human), enter a coordinate (column and line): ";
        // Getting column
        if (cin >> column) 
        {
            column = toupper(column);
            col_index = column - 'A';
            if ((col_index < 0) || (col_index > board_size - 1))  // column out of range
            {
                cout << "Invalid column: " << column << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }   // else evaluate line number
        }
        else
        {
            cout << "Please enter a valid column character." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // Getting line number
        if (cin >> line)
        {
            // Verify range validity
            if ((line >= 1) && (line <= board_size))
            {
                // Verify if move can be placed
                if (board.set_pos_value(col_index, line-1, color))
                {
                    cin.clear(); // Clear buffer to prevent repeated moves
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;      // valid input, go check for winner
                }
                else
                {
                    cout << "Position already taken: " << column << line << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;                    
                }
            }
            else
            {
                cout << "Invalid line number: " << line << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        }
        else
        {
            cout << "Please enter a valid line number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }        
    } // end for
    
    // Verify if the play has win the game
    return board.verify_winner(color);
}

// Calculate next computer play
bool HexGame::get_computer_play(HexSpot color)
{
    cout << endl << "> " << PLAYER_LABEL.at(color) << " player (computer) is evaluating the next move... " << endl;

    HexSpot player;
    PosCoord rnd_move;
    size_t possible_moves = board.free_spaces.size();       // Get number of valid moves
    vector<int> move_score(possible_moves, 0);              // Initialize vector to accumulate number of wins for each move
    int move_id = 0, best_move_id = 0, best_move_score = 0; // Initialize move decision variables
    
    // Iterate over possible moves running a Monte Carlo simulation for each of them. Finally chooses move with best score.
    for (auto it = board.free_spaces.begin(); it != board.free_spaces.end(); ++it, ++move_id)
    {
        for (unsigned  run = 0; run < mc_trials; ++run)                 // Run configurable number of Monte Carlo trials
        {
            aux_board.copy_board(board);                                // Copy game board to a auxiliary one
            aux_board.set_pos_value(it->first, it->second, color);      // Make move that is being tested on the aux board
            player = color;
            for (size_t i = 1; i < possible_moves; ++i)                 // Fill all other free spaces with random moves
            {
                player = (player == BLUE ? RED : BLUE);                 
                rnd_move = aux_board.random_free_space();
                aux_board.set_pos_value(rnd_move.first, rnd_move.second, player);
            }
            if (aux_board.verify_winner(color))                         // Check if computer player has won to increment move score
                ++move_score[move_id];
        }
        if (move_score[move_id] > best_move_score)                      // After Monte Carlo trials, check if this move is the best
        {                                                               // move up to now. Update best move if it is a better one.
            best_move_score = move_score[move_id];
            best_move_id = move_id;
        }
    }

    // Inform if there was no winning move. This should not happen.
    if (best_move_score == 0)
        cout << "No winning condition!" << endl;
    
    // Make the selected best move in the real game board
    auto pos_it = board.free_spaces.begin();                            
    advance(pos_it, best_move_id);              
    board.set_pos_value(pos_it->first, pos_it->second, color);
    
    // Inform the computer move
    cout << endl << "> " << PLAYER_LABEL.at(color) << " player (computer) plays at coordinate: ";
    cout << static_cast<char>('A' + pos_it->first) << pos_it->second + 1 << endl;
    
    // Verify if the play has win the game
    return board.verify_winner(color);    
}

// Calculate next computer play
bool HexGame::get_next_move(HexSpot color)
{
   if (players[color] == HUMAN)
       return get_human_play(color);
   else
       return get_computer_play(color);
}


// Get the user input if a new game should be started
bool HexGame::play_again()
{
    return make_yn_question("Do you want to play again (Y or N)? ");
}


//----------------------
// Private functions
//----------------------

// Get the user input for a yes or no question
bool HexGame::make_yn_question(string question)
{
    char cont;
    for (;;)
    {
        cout << endl << question;
        if (cin >> cont)
        {
            if (toupper(cont) == 'N')
                return false;
            else if (toupper(cont) == 'Y')
                return true;
            else
                cout << "Please enter a valid answer." << endl;
        }
        else
        {
            cout << "Please enter a valid answer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
