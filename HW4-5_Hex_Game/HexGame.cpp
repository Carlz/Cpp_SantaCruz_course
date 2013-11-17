/* 
 * File:   HexGame.cpp
 * Author: hp
 * 
 * Created on 16 de Novembro de 2013, 19:04
 */

#include <limits>
#include "HexGame.h"

HexGame::HexGame() {
}

HexGame::HexGame(const HexGame& orig) {
}

HexGame::~HexGame() {
}


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

void HexGame::get_human_play(HexSpot color)
{
    char column;
    unsigned col_index, line;
    
    for (;;)
    {
        cout << endl << "Player " << player_string.at(static_cast<int>(color)) << " - enter coordinate (column and line): ";
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
            if ((line >= 1) && (line <= board_size))
            {
                if (board.set_pos_value(col_index, line-1, color))
                {
                    break;      // valid input
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
}
