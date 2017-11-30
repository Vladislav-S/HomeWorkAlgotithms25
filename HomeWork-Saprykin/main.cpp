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
    cout << argv[0] << endl;
    Map m;
    AS::AStar A;
    m.start(argc, argv);
    m.Print();
    try {
         A.Work(m);
    } catch (const AS::my_exception & ex) {
        cout << ex.What() << endl;
    } catch (const exception & ex){
       cout << ex.what() << endl;
    }
   

    return 0;
}
