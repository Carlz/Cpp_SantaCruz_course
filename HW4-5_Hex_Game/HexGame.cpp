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

// Calculate next computer play
bool HexGame::get_computer_play(HexSpot color)
{
    size_t possible_moves = board.free_spaces.size();
    PosCoord rnd_move;
    vector<int> move_win_cnt(possible_moves, 0);
    HexSpot player;
    int move_id = 0, best_move_id = 0, best_move_cnt = 0;
    for (auto it = board.free_spaces.begin(); it != board.free_spaces.end(); ++it, ++move_id)
    {
        for (unsigned  run = 0; run < MC_TRIALS; ++run)
        {
            aux_board.copy_board(board);
            aux_board.set_pos_value(it->first, it->second, color);      // Set move that is being tested
            player = color;
            for (size_t i = 1; i < possible_moves; ++i)
            {
                player = (player == BLUE ? RED : BLUE);
                rnd_move = aux_board.random_free_space();
                aux_board.set_pos_value(rnd_move.first, rnd_move.second, player);
            }
            if (aux_board.verify_winner(color))
                ++move_win_cnt[move_id];
//            cout << aux_board;
        }
        if (move_win_cnt[move_id] > best_move_cnt)
        {
            best_move_cnt = move_win_cnt[move_id];
            best_move_id = move_id;
        }
//        cout << move_id << ": " << move_win_cnt[move_id] << endl;
    }

    auto pos_it = board.free_spaces.begin();
    advance(pos_it, best_move_id);              // treat case when bes_move_cnt is 0 = never wins
    board.set_pos_value(pos_it->first, pos_it->second, color);
    
    // Verify if the play has win the game
    return board.verify_winner(color);    
}
