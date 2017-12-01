//
//  AStar.cpp
//  HomeWork-Saprykin
//
//  Created by Vlad Saprykin on 26.11.2017.
//  Copyright © 2017 Vlad Saprykin. All rights reserved.
//

#include "headers/AStar.hpp"

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

shared_ptr<Point> AS::AStar::find_min_in_set_between2(const shared_ptr<Point> & a, const shared_ptr<Point> & b, set<shared_ptr<Point>> s){
    //a, b, s
    shared_ptr<Point> tmp;
    double D = INFINITY; //distance
    for(auto i : s){
        if((distance(i, a) + distance(i, b)) < D){
            D = distance(i, a) + distance(i, b);
            tmp = i;
        }
    }
    
    return tmp;
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

void AS::AStar::Work(Map & m){
    vector<shared_ptr<Point>> path =
    FindPath(m.whereIsHeroSymbol(), m.whereIsExitSymbol(), m);
    if(path.empty()){
        throw my_exception("no way to exit");
    }
    PrintPath(path);
}
vector<shared_ptr<Point>> AS::AStar::FindPath(shared_ptr<Point> _start, shared_ptr<Point> _finish, Map & m){
    //при углублении, передача start-finish, сохраняет свои направления
    set<shared_ptr<Point>> closedSet;
    set<shared_ptr<Point>> openSet;
    vector<shared_ptr<Point>> pathMapset; // change to vector - done
    //тест
    //start.get()->
    shared_ptr<Point> start(make_shared<Point>(_start.get()->m, _start.get()->n));
    shared_ptr<Point> finish(make_shared<Point>(_finish.get()->m, _finish.get()->n));
    
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
            pathMapset = reconstruct_Path(start, finish);
            //PrintPath(pathMapset);
            return pathMapset;
        }
        
        
        openSet.erase(X);
        closedSet.insert(X);
        //cout << m.Neighbors(X).size() << endl;
        for(auto Y : m.Neighbors(X)){
            //если У среди посещенных, пропускаем
            if(isPointerInSet(Y, closedSet)){
                continue;
            }
            //if y is door or key
            if(m.isDoor(Y)){

                if(!isPointerInSet(Y, doors) && !isPointerInSet(Y, visited_doors)){
                    doors.insert(Y);
                }
                if(Y != finish && !isPointerInSet(Y, visited_doors)){ //я что-то сделал и оно заработало
                    continue; //если идем от ключа до двери, дверь как финиш
                }
            }else if(m.isKey(Y)){
                //если не использованный и не посещенный
                if(!isPointerInSet(Y, keys) && !isPointerInSet(Y, visited_keys)){
                    keys.insert(Y);
                }//
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
    
    //если не обнаружили пути выхода
    //проверить, есть ли двери
    while(!doors.empty()){

        //найти выгодную дверь
        shared_ptr<Point> _door = find_min_in_set_between2(start, finish, doors);
        //найти ближайший ключ
        shared_ptr<Point> _key = find_min_in_set_between2(start, _door, keys);
        //если нет ключей - break
        if(_key.get() == nullptr) break; //можно проверять в начале цикла
        
        //проложить путь от старта до ключа
        vector<shared_ptr<Point>> _pathToKey = FindPath(start, _key, m);
        keys.erase(_key);
        visited_keys.insert(_key);
        //если нет пути, удалить ключ, continue //нет необходимости //notodo
        if(_pathToKey.empty()){
            //nothing
        }
        //проложить путь от ключа до двери
        vector<shared_ptr<Point>> _pathToDoor = FindPath(_key, _door, m);
        doors.erase(_door);
        visited_doors.insert(_door);
        //если нет пути, удалить ключ, continue //notodo
        if(_pathToDoor.empty()){
            //nothing
        }
        
        //получить путь от двери до финиша
        vector<shared_ptr<Point>> _pathMapSet = FindPath(_door, finish, m);
        //если путь есть - return путь
        if(!_pathMapSet.empty()){
            //вернуть объединенный путь
            _pathMapSet.insert(_pathMapSet.end(), _pathToDoor.begin(), _pathToDoor.end());
            _pathMapSet.insert(_pathMapSet.end(), _pathToKey.begin(), _pathToKey.end());
            return _pathMapSet;
        }
    
        //если пути нет, удалить дверь, continue
        //doors.erase(_door); //а оно нам надо? //оставлю пока так
    }
    return pathMapset; //вернуть пустое множество, означает, что пути нет
}





























