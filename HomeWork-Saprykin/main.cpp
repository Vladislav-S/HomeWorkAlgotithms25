//
//  main.cpp
//  HomeWork-Saprykin
//
//  Created by Vlad Saprykin on 26.11.2017.
//  Copyright © 2017 Vlad Saprykin. All rights reserved.
//
#include "headers/map.h"
#include "headers/AStar.hpp"

using namespace std;

int main(int argc, char * argv[]) {
    try {
        cout << argv[0] << endl;
        Map m(argc, argv);
        AS::AStar A;
        m.start();
        m.Print();
        A.Work(m);
    } catch (const my_exception & ex) {
        cout << ex.What() << endl;
    } catch (const exception & ex){
       cout << ex.what() << endl;
    }
    return 0;
}
