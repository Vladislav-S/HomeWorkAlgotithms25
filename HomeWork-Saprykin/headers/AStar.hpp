//
//  AStar.hpp
//  HomeWork-Saprykin
//
//  Created by Vlad Saprykin on 26.11.2017.
//  Copyright © 2017 Vlad Saprykin. All rights reserved.
//

#ifndef AStar_hpp
#define AStar_hpp

//#include "base.h"
#include "map.h"
using namespace std;
using Cords = pair<int, int>;
namespace AS {
    struct PointCmp{
        bool operator() (const Point & a, const Point & b){
            return a.m == b.m && a.n == b.n;
        }
        bool operator() (const shared_ptr<Point> & a, const shared_ptr<Point> & b){
            return a.get()->m == b.get()->m && a.get()->n == b.get()->n;
        }
    };
    class AStar{
        //set<shared_ptr<Point>, PointCmp> closedSet;
        //set<shared_ptr<Point>, PointCmp> openSet;
        //set<Point, PointCmp> pathMapset; // change to vector
        shared_ptr<Point> find_min_f(const set<shared_ptr<Point>> &);
        double distance(shared_ptr<Point> A, shared_ptr<Point> B);
        vector<shared_ptr<Point>> reconstruct_Path(const shared_ptr<Point> &start, const shared_ptr<Point> &finish);
        vector<shared_ptr<Point>> GlobalPath;
        void PrintPath(const vector<shared_ptr<Point>> & _v);
        bool isPointerInSet(const shared_ptr<Point> & p, set<shared_ptr<Point>>  s);
    public:
        AStar() = default;
        void FindPath(shared_ptr<Point> start, shared_ptr<Point> finish , Map &);
        
    };
}
#endif /* AStar_hpp */
