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
//using namespace std;
//using Cords = pair<int, int>;
namespace AS {

    class AStar{
        set<shared_ptr<Point>> doors; ///Обнаруженные двери
        set<shared_ptr<Point>> keys; ///обнаруженные ключи
        set<shared_ptr<Point>> visited_doors; ///посещенные двери
        set<shared_ptr<Point>> visited_keys; ///посещенные ключи
        shared_ptr<Point> find_min_f(const set<shared_ptr<Point>> &); ///поиск минимальной f
        shared_ptr<Point> find_min_in_set_between2(const shared_ptr<Point> & a, const shared_ptr<Point> & b, set<shared_ptr<Point>> s); ///поиск минимального расстояния между тремя точками
        double distance(shared_ptr<Point> A, shared_ptr<Point> B); ///расстояние между точками
        vector<shared_ptr<Point>> reconstruct_Path(const shared_ptr<Point> &start, const shared_ptr<Point> &finish); ///реконструирование пути
        void PrintPath(const vector<shared_ptr<Point>> & _v); ///печать пути
        bool isPointerInSet(const shared_ptr<Point> & p, set<shared_ptr<Point>>  s); ///есть ли Point в множестве
        vector<shared_ptr<Point>> FindPath(shared_ptr<Point> start, shared_ptr<Point> finish , Map &); ///функция поиска пути

    public:
        AStar() = default; ///конструктор по умолчанию
        void Work(Map &); ///запуск алгоритма поиска
        
    };
    
}
#endif /* AStar_hpp */
