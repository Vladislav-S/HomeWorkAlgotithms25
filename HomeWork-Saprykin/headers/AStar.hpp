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
//struct Point {
//        int m;
//        int n;
//        double g; //стоимость пути от начальной вершины
//        double h; //Эвристическая оценка расстояния до цели
//        double f;
//        Point(int _m, int _n);
//        Point(Cords c);
//        bool operator== (const Point & b){
//            return m == b.m && n == b.n;
//        }
//    };
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
        shared_ptr<Point> find_min_f(const set<shared_ptr<Point>, PointCmp> &);
        double distance(shared_ptr<Point> A, shared_ptr<Point> B);
        
    public:
        AStar() = default;
        void FindPath(shared_ptr<Point> start, shared_ptr<Point> finish , Map &);
    };
}
#endif /* AStar_hpp */
