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
using namespace std;
using Cords = pair<int, int>;

struct Point {
    int m; //координата по высоте
    int n; //координата по ширине
    double g; //стоимость пути от начальной вершины
    double h; //Эвристическая оценка расстояния до цели
    double f;
    shared_ptr<Point> came_from;
    Point(int _m, int _n){m = _m; n = _n;}
    Point(Cords c){
        m = c.first; //проверить
        n = c.second;
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
    void copy_coords(const shared_ptr<Point> &p){
        m = p.get()->m; n = p.get()->n;
    }
};

bool operator==(const shared_ptr<Point> & l, const shared_ptr<Point> & r);

class Map{
private:
    int argc{0};
    char** argv;
    matrix<char> m; ///матрица карты
    
    char symbols[11] = {'\n', ' ', '#', '@', '*', 'u', 'r', 'd', 'l', 'D', 'k'}; //0-dont override 1-space 2-obstacle, 3-hero,
    //4-exit, 5-only up, 6-only right, 7-only down, 8-only left, 9-door, 10-key
    void parse_file(char *);
    bool out_of_range(int _m, int _n);

public:
    Map() = default; ///стандартный конструктор
    Map(int argc, char *argv[]); ///конструктор с параметрами
    vector<shared_ptr<Point>> Neighbors(shared_ptr<Point> p); ///поиск соседей точки \details в 4х направлениях
    void start(); ///начало парсинга
    void start(int argc, char *argv[]); ///начало парсинга \details если экземпляр инициализирован без параметров
    shared_ptr<Point> whereIsHeroSymbol(); ///вернуть указатель на символ героя
    shared_ptr<Point> whereIsExitSymbol(); ///вернуть указатель на символ выхода
    bool isDoor(const shared_ptr<Point> & p); ///символ по указателю дверь?
    bool isKey(const shared_ptr<Point> & p); ///сивол по указателю ключ?

    void Print(){m.Print();} ///печать карты в стандартный поток вывода
    
};

///класс ошибки
class my_exception{
    string what;
public:
    my_exception(string _what) : what(_what){;}
    string What() const {return what;}
};
#endif /* map_h */
