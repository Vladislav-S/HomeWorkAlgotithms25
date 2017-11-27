//
//  main.cpp
//  HomeWork-Saprykin
//
//  Created by Vlad Saprykin on 26.11.2017.
//  Copyright © 2017 Vlad Saprykin. All rights reserved.
//
#include "headers/map.h"
#include "headers/AStar.hpp"
//#include <iostream>
using namespace std;

int main(int argc, char * argv[]) {
    // insert code here...
    //cout << argv[0] << endl;
    Map m;
    AS::AStar A;
    m.start(argc, argv);
    A.FindPath(m.whereIsHeroSymbol(), m.whereIsExitSymbol(), m);

    //std::cout << "Hello, World!\n";
    return 0;
}
