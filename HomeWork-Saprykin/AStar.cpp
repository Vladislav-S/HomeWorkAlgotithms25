//
//  AStar.cpp
//  HomeWork-Saprykin
//
//  Created by Vlad Saprykin on 26.11.2017.
//  Copyright © 2017 Vlad Saprykin. All rights reserved.
//

#include "headers/AStar.hpp"

//AS::Point::Point(int _m, int _n){
//    m = _m; n = _n;
//}
//AS::Point::Point(Cords c){
//    m = c.second; //проверить
//    n = c.first;
//}

double AS::AStar::distance(shared_ptr<Point> A, shared_ptr<Point> B){
    return sqrt(pow(B.get()->n-A.get()->n, 2)+pow(B.get()->m-A.get()->m, 2));
}
shared_ptr<Point> AS::AStar::find_min_f(const set<shared_ptr<Point>> & s){
    double f = INFINITY;
    shared_ptr<Point> p;
    for(auto a : s){
        if(a->f < f){
            f = a->f;
            p = a;
        }
    }
    return p;
}

vector<shared_ptr<Point>> AS::AStar::reconstruct_Path(const shared_ptr<Point> &start, const shared_ptr<Point> &finish){
    vector<shared_ptr<Point>> v;
    shared_ptr<Point> current = finish;
    while(current.get()->came_from != nullptr){
        v.push_back(current);
        current = current.get()->came_from;
    }
    v.push_back(start);
    return v;
}
void AS::AStar::PrintPath(const vector<shared_ptr<Point>> & _v){
    for(auto a : _v){
        cout << a.get()->m << "-" << a.get()->n << endl;
    }
}
bool AS::AStar::isPointerInSet(const shared_ptr<Point> & p, set<shared_ptr<Point>> s){
    for(auto a : s){
        if(a == p) return true;
    }
    return false;
}
void AS::AStar::FindPath(shared_ptr<Point> start, shared_ptr<Point> finish, Map & m){
    set<shared_ptr<Point>> closedSet;
    set<shared_ptr<Point>> openSet;
    vector<shared_ptr<Point>> pathMapset; // change to vector

    start.get()->g = 0;
    start.get()->h = distance(start, finish);
    start.get()->f = start.get()->g + start.get()->h;
    
    openSet.insert(start);
    
    while (!openSet.empty()){
        // x = вершина из openset  с наименьшим f
        shared_ptr<Point> X = find_min_f(openSet);
        if(X == finish){
            //reconstruct_path
            finish = X; //издержки С++
            GlobalPath = reconstruct_Path(start, finish);
            PrintPath(GlobalPath);
            return;
        }
        
        openSet.erase(X);
        closedSet.insert(X);
        cout << m.Neighbors(X).size() << endl;
        for(auto Y : m.Neighbors(X)){
            //если У среди посещенных, пропускаем
            if(isPointerInSet(Y, closedSet)){
                continue;
            }
            //вычисляем g(x) для обрабатываемого соседа
            double tentative_g_score = X.get()->g + distance(X, Y);
            bool tentative_is_better{false};
            //Если сосед не в открытом списке, добавим его туда
            //туду: не ищет указатели
            if(!isPointerInSet(Y, openSet)){
                openSet.insert(Y);
                tentative_is_better = true;
            }else{
                if(tentative_g_score < Y.get()->g){
                    tentative_is_better = true;
                }
            }
            
            //объявление свойств соседа
            if(tentative_is_better){
                Y.get()->came_from = X; //откуда пришли
                Y.get()->g = tentative_g_score;
                Y.get()->h = distance(Y, finish);
                Y.get()->f = Y.get()->g + Y.get()->h;
            }
        }
    }
    return;
}





























