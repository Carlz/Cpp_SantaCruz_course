/* 
 * File:   main.cpp
 * Author: Capacitare
 *
 * Created on November 15, 2013, 11:11 AM
 */

#include <cstdlib>
#include "Graph.h"
#include "HexBoard.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    HexBoard b(8);
    
    b.set_pos_value(3,5,RED_SPOT);
    b.set_pos_value(6,0,BLUE_SPOT);
    b.set_pos_value(1,3,RED_SPOT);
    b.set_pos_value(7,2,BLUE_SPOT);
    b.set_pos_value(4,7,RED_SPOT);
    
    cout << b;
    
    return 0;
}

