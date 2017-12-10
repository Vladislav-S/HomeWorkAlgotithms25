//
//  AStar.hpp
//  HomeWork-Saprykin
//
//  Created by Vlad Saprykin on 26.11.2017.
//  Copyright © 2017 Vlad Saprykin. All rights reserved.
//

#ifndef AStar_hpp
#define AStar_hpp

#include "map.h"

namespace AS {

    class AStar{
        //set<shared_ptr<Point>> doors; ///Обнаруженные двери
        //set<shared_ptr<Point>> keys; ///обнаруженные ключи
        set<shared_ptr<Point>> visited_doors; ///посещенные двери
        set<shared_ptr<Point>> visited_keys; ///посещенные ключи
        shared_ptr<Point> find_min_f(const set<shared_ptr<Point>> &); ///поиск минимальной f
        //гshared_ptr<Point> find_min_in_set_between2(const shared_ptr<Point> & a, const shared_ptr<Point> & b, const set<shared_ptr<Point>>& s); ///поиск минимального расстояния между тремя точками
        double distance(const shared_ptr<Point> &A,const shared_ptr<Point> & B); ///расстояние между точками
        vector<shared_ptr<Point>> reconstruct_Path(const shared_ptr<Point> &start, const shared_ptr<Point> &finish); ///реконструирование пути
        void PrintPath(const vector<shared_ptr<Point>> & _v); ///печать пути
        bool isPointerInSet(const shared_ptr<Point> & p, set<shared_ptr<Point>>  s); ///есть ли Point в множестве
        bool isPointerInVect(const shared_ptr<Point> & p, const vector<shared_ptr<Point>> & v);
        vector<shared_ptr<Point>> FindPath(shared_ptr<Point> start, shared_ptr<Point> finish , Map &); ///функция поиска пути
        vector<shared_ptr<Point>> FindPaths(shared_ptr<Point> start, shared_ptr<Point> finish , Map &); ///обертка для поиска всех возможных путей
        
        vector<shared_ptr<Point>> DoorsInPath(const vector<shared_ptr<Point>> & path, Map & m);
        vector<shared_ptr<Point>> FindKeysForDoors(const vector<shared_ptr<Point>> & doors, const shared_ptr<Point> & start, Map & m);
        vector<shared_ptr<Point>> sortKeys(const set<shared_ptr<Point>> & keys, const shared_ptr<Point> & start);
    public:
        AStar() = default; ///конструктор по умолчанию
        void Work(Map &); ///запуск алгоритма поиска
        
    };
    
}
#endif /* AStar_hpp */
