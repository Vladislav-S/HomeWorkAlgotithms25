//
//  map.h
//  HomeWork-Saprykin
//
//  Created by Vlad Saprykin on 26.11.2017.
//  Copyright © 2017 Vlad Saprykin. All rights reserved.
//

#ifndef map_h
#define map_h

#include "base.h"
#include "matrix.h"
//#include "graph.h"
using namespace std;
using Cords = pair<int, int>;
using bAndCords = pair<bool, vector<Cords>>;
using dataAndCords = pair<vector<int>, vector<Cords>>; //(int)canGoBack, doors, keys

struct Point {
    int m;
    int n;
    double g; //стоимость пути от начальной вершины
    double h; //Эвристическая оценка расстояния до цели
    double f;
    shared_ptr<Point> came_from;
    Point(int _m, int _n){m = _m; n = _n;}
    Point(Cords c){
        m = c.second; //проверить
        n = c.first;
    }
    Point(const Point & p){
        m = p.m; n=p.n; g=p.g; h=p.h; f=p.f;
    }
    Point(const shared_ptr<Point> p){
        m=p.get()->m; n=p.get()->n; g=p.get()->g; h=p.get()->h; f=p.get()->f;
    }
    bool operator== (const Point & b){
        return m == b.m && n == b.n;
    }
};

class Map{
private:
    int argc{0};
    char** argv;
    matrix<char> m; //матрица карты в визуальном представлении
    matrix<bool> m1; //матрица посещенных участков
    matrix<dataAndCords> m2; // матрица для хранения посещенных разветвлений
    char symbols[11] = {'\n', ' ', '#', '@', '*', 'u', 'r', 'd', 'l', 'D', 'k'}; //0-dont override 1-space 2-obstacle, 3-hero,
    //4-exit, 5-only up, 6-only right, 7-only down, 8-only left, 9-door, 10-key
    enum way {up = 0, right = 1, down = 2, left = 3};
    void parse_file(char *);
    //Graph g;
    //Cords heroCords;
public:
    Map() = default;
    Map(int argc, char *argv[]);
    vector<shared_ptr<Point>> Neighbors(shared_ptr<Point> p);
    void start();
    void start(int argc, char *argv[]);
    shared_ptr<Point> whereIsHeroSymbol();
    shared_ptr<Point> whereIsExitSymbol();

    
};
#endif /* map_h */
