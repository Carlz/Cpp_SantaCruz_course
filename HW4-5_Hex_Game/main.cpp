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

    Graph g;
    
    HexBoard b(3);
    
    cout << b;
    
    return 0;
}

