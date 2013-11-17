/* 
 * File:   main.cpp
 * Author: Capacitare
 *
 * Created on November 15, 2013, 11:11 AM
 */

#include <cstdlib>
#include "Graph.h"
#include "HexBoard.h"
#include "HexGame.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    HexGame game;
    game.greetings();
    for (;;)
    {
        game.start_game();
        for (int i = 0; i < 3; ++i)
        {
            game.print_board();
            game.get_human_play(BLUE);
            game.print_board();
            game.get_human_play(RED);
        }
    }
    
    return 0;
}

