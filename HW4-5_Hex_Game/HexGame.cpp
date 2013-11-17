////////////////////////////////////////////////////////////////////////////////
/// \brief      Hex Game class implementation
/// \author     Carlos Sampaio
/// \file       HexGame.cpp
/// \date       16/11/2013
///
///     Hex Game class implements the control structures for the game play.
///
////////////////////////////////////////////////////////////////////////////////

#include <limits>
#include "HexGame.h"

// Get user inputs to initialize the game board and start the game
void HexGame::start_game()
{
    unsigned nplayer, bsize;
    
    // Get the number of players input 
    if (false)  // enable when computer AI is implemented
    {
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
        human_player = nplayer;
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
    board_size = bsize;
}

// Get the user play input and checks for a winner, if game has ended return true, else false.
bool HexGame::get_human_play(HexSpot color)
{
    char column;
    unsigned col_index, line;
    
    for (;;)
    {
        cout << endl << "> " << PLAYER_LABEL.at(color) << " player, enter a coordinate (column and line): ";
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

// Get the user input if a new game should be started
bool HexGame::play_again()
{
    char cont;
    for (;;)
    {
        cout << endl << "Do you want to play again (Y or N)? ";
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
