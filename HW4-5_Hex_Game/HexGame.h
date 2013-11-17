/* 
 * File:   HexGame.h
 * Author: hp
 *
 * Created on 16 de Novembro de 2013, 19:04
 */

#include "HexBoard.h"
using namespace std;

#ifndef HEXGAME_H
#define	HEXGAME_H

class HexGame {
public:
    HexGame();
    HexGame(const HexGame& orig);
    virtual ~HexGame();
    
    void greetings()
        { cout << "Welcome to Hex Game v" << HEX_VERSION_MAJOR << "." << HEX_VERSION_MINOR << " !" << endl;}
    void start_game();
    void print_board()
        { cout << board;}
    void get_human_play(HexSpot color);
    
    
private:
    const unsigned HEX_VERSION_MAJOR = 1;
    const unsigned HEX_VERSION_MINOR = 0;
    const vector<string> player_string = {"NONE", "BLUE", "RED"};
    HexBoard board;
    unsigned board_size;

};

#endif	/* HEXGAME_H */

