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
        set<shared_ptr<Point>> doors;
        set<shared_ptr<Point>> keys;
        set<shared_ptr<Point>> visited_doors;
        set<shared_ptr<Point>> visited_keys;
        shared_ptr<Point> find_min_f(const set<shared_ptr<Point>> &);
        shared_ptr<Point> find_min_in_set_between2(const shared_ptr<Point> & a, const shared_ptr<Point> & b, set<shared_ptr<Point>> s);
        double distance(shared_ptr<Point> A, shared_ptr<Point> B);
        vector<shared_ptr<Point>> reconstruct_Path(const shared_ptr<Point> &start, const shared_ptr<Point> &finish);
        vector<shared_ptr<Point>> GlobalPath;
        void PrintPath(const vector<shared_ptr<Point>> & _v);
        bool isPointerInSet(const shared_ptr<Point> & p, set<shared_ptr<Point>>  s);
    public:
        AStar() = default;
        vector<shared_ptr<Point>> FindPath(shared_ptr<Point> start, shared_ptr<Point> finish , Map &);
        void Work(Map &);
        
    };
    class my_exception{
        string what;
    public:
        my_exception(string _what) : what(_what){;}
        string What() const {return what;}
    };
}
#endif /* AStar_hpp */
