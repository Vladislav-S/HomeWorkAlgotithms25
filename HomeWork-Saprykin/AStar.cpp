//
//  AStar.cpp
//  HomeWork-Saprykin
//
//  Created by Vlad Saprykin on 26.11.2017.
//  Copyright © 2017 Vlad Saprykin. All rights reserved.
//

#include "headers/AStar.hpp"

double AS::AStar::distance(const shared_ptr<Point> &A, const shared_ptr<Point> &B){
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

//shared_ptr<Point> AS::AStar::find_min_in_set_between2(const shared_ptr<Point> & a, const shared_ptr<Point> & b, const set<shared_ptr<Point>> & s){
//    //a, b, s
//    shared_ptr<Point> tmp;
//    double D = INFINITY; //distance
//    for(auto i : s){
//        if((distance(i, a) + distance(i, b)) < D){
//            D = distance(i, a) + distance(i, b);
//            tmp = i;
//        }
//    }
//
//    return tmp;
//}

vector<shared_ptr<Point>> AS::AStar::reconstruct_Path(const shared_ptr<Point> &start, const shared_ptr<Point> &finish){
    //IMPORTANT
    //в этом месте, последнее появление этих объектов в алгоритме поиска, далее они должны быть впихнуты только в путь
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

bool AS::AStar::isPointerInVect(const shared_ptr<Point> & p, const vector<shared_ptr<Point>> & v){
    for(auto a : v){
        if(p == a) return true;
    }
    return false;
}

void AS::AStar::Work(Map & m){
    vector<shared_ptr<Point>> path =
    FindPaths(m.whereIsHeroSymbol(), m.whereIsExitSymbol(), m);
    if(path.empty()){
        throw my_exception("no way to exit");
    }
    PrintPath(path);
}

vector<shared_ptr<Point>> AS::AStar::DoorsInPath(const vector<shared_ptr<Point>> & path, Map & m){
    vector<shared_ptr<Point>> v;
    for(auto a : path){
        if(m.isDoor(a)){
            v.push_back(a);
        }
    }
    reverse(v.begin(), v.end());
    return v;
}

vector<shared_ptr<Point>> AS::AStar::FindKeysForDoors(const vector<shared_ptr<Point>> & doors, const shared_ptr<Point> & start, Map & m){
    //добавить двери в список, чтоб небыло повторяющихся
    set<shared_ptr<Point>> doorsTmpSet;
    set<shared_ptr<Point>> _keys;
    _keys.clear();
    set<shared_ptr<Point>> _keyss;
    
    for(auto a : doors){
        if(!isPointerInSet(a, doorsTmpSet)){
            doorsTmpSet.insert(a);
        }
    }
// //для каждой двери найти ключи того же типа
//
    for(auto a: doorsTmpSet){
        vector<shared_ptr<Point>> tmp = m.whereIsSymbols(a);
        //keys.insert(keys.end(), tmp.begin(), tmp.end());
        for(auto b : tmp){
            if(!isPointerInSet(b, _keys) && !isPointerInSet(b, visited_keys)){
                _keys.insert(b);
            }
        }
    }
//    //сопоставить количество ключей с дверьми
    if(_keys.size() > doors.size()){
        vector<shared_ptr<Point>> doorsCopy = doors;
        set<shared_ptr<Point>> keysCopy = _keys;
        for(auto a : doors){

            for(auto b : keysCopy){
                if(m.isKeyForDoor(b, a)){
                    keysCopy.erase(b);
                    break;
                }
            }
        }
        //удалить ненужные ключи
        for(auto c : keysCopy){
            _keys.erase(c);
        }
    }
    //отсортировать ключи по расстоянию между ними и стартовой точкой ///мб отдельно
    //vector<shared_ptr<Point>> keys;
//
    return sortKeys(_keys, start);
}
//
vector<shared_ptr<Point>> AS::AStar::sortKeys(const set<shared_ptr<Point>> & keys, const shared_ptr<Point> & start){
    double minDist = INFINITY;
    shared_ptr<Point> current = start;

    vector<shared_ptr<Point>> v;
    for(auto a{0}; a < keys.size(); a++){
        shared_ptr<Point> tmp;
        for(auto b : keys){
            //продолжает хождение, если расстояние больше, при этом, пихает лишний ключ
            if(distance(current, b) < minDist && !isPointerInVect(b, v) && current != b){ //добавил это и вроде заработало
                minDist = distance(current, b);
                tmp = b;
                continue;
            }
            
        }
        //теперь у нас добавляется один и тот же ключ несколько раз - сделать проверку на вхождение
        v.push_back(tmp);
        minDist = INFINITY;
        current = v.at(v.size()-1);
    }
    return v;
    //return set<shared_ptr<Point>>();
}


/*
 итого - либо
 течет где-то память либо
 ОС оптимизирует память по собственному желанию либо
 магия, разобраться какого хрена это происходит
 */
vector<shared_ptr<Point>> AS::AStar::FindPaths(shared_ptr<Point> __start, shared_ptr<Point> __finish , Map & m){
    //начинай свой день с новыми объектами вместо старых
    shared_ptr<Point> start(make_shared<Point>(__start.get()->m, __start.get()->n));
    shared_ptr<Point> finish(make_shared<Point>(__finish.get()->m, __finish.get()->n));
    
    cout << "In FindPaths beginning: " << start.get()->m << "-" << start.get()->n << " " << finish.get()->m << "-" << finish.get()->n << endl;
    vector<shared_ptr<Point>> path = FindPath(start, finish, m);
    vector<shared_ptr<Point>> doors = DoorsInPath(path, m);
    //return path;
    reverse(path.begin(), path.end());
    //проверить, есть ли путь вообще
    if(path.empty() || doors.empty()){
        cout << "DEBUG" << endl;
        return path; //исчезают данные
    }
    
    for(int a{0}; a < doors.size(); ++a){
            //cout << "shitty bug under here" << endl;
        if(isPointerInSet(doors.at(a), visited_doors)){
            doors.erase(doors.begin()+a); //у нас уменьшается вектор, но при этом индекс не изменяется
            --a; //поэтому надо уменьшить текущий индекс на 1
        }
    }
    if(doors.empty()){
        return path;
    }
    //найти все необходимые ключи
    vector<shared_ptr<Point>> keys = FindKeysForDoors(doors, start ,m); //добавляет лишний ключ
    reverse(keys.begin(), keys.end());
    //vector<shared_ptr<Point>> keys = sortKeys(tmp1, start); //пока не самые лучшие варианты ключей //хотя нет, все норм
    //найти пути до всех ключей
    shared_ptr<Point> _start = start; //путь от старта до финиша с ключами
    
    //vector<shared_ptr<Point>> _path;
    path.clear(); //очищение через омовение кровью
    for(int a{0}; a < keys.size(); ++a){
        
        shared_ptr<Point> _finish = keys.at(a);
        vector<shared_ptr<Point>> __path;
        __path = FindPaths(_start, _finish, m);
        if(__path.empty()){
            return __path; //если пути не существует
        }
        //cout << "Path: " << endl;
        //PrintPath(__path);
        path.insert(path.end(), __path.begin(), __path.end());
        visited_keys.insert(keys.at(a)); //добавим ключ в посещенные
        _start = keys.at(a);
    }
    
    //добавляем двери в список посещенных дверей
    for(auto a : doors){
        visited_doors.insert(a);
    }
    //ищем путь от последнего ключа до финиша
    vector<shared_ptr<Point>> __path;
    __path = FindPaths(keys.at(keys.size()-1), finish, m);
    
    if(__path.empty()) return __path;
    path.insert(path.end(), __path.begin(), __path.end());
    //добавить пройденные двери и ключи в глобальное множество
    
    return path;
}

//передаем копии указателей // а оно нам надо? // по хорошему, надо передавать копии объектов, ибо че с элементами происходит?
vector<shared_ptr<Point>> AS::AStar::FindPath(shared_ptr<Point> _start, shared_ptr<Point> _finish, Map & m){
    //при углублении, передача start-finish, сохраняет свои направления
    set<shared_ptr<Point>> closedSet;
    set<shared_ptr<Point>> openSet;
    vector<shared_ptr<Point>> pathMapset; // change to vector - done
    //тест
    //start.get()->
    //мы создаем копии старта и финиша, и возвращаем путь// все как задуманно
    shared_ptr<Point> start(make_shared<Point>(_start.get()->m, _start.get()->n));
    shared_ptr<Point> finish(make_shared<Point>(_finish.get()->m, _finish.get()->n));
    
    start.get()->g = 0;
    start.get()->h = distance(start, finish);
    start.get()->f = start.get()->g + start.get()->h;
    
    openSet.insert(start);
    
    while (!openSet.empty()){
        // x = вершина из openset  с наименьшим f
        shared_ptr<Point> X = find_min_f(openSet);
        
        //ЕСЛИ ФИНИШ
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

    return pathMapset; //вернуть пустое множество, означает, что пути нет
}

/*

 на завтра - понять, куда делся путь от предпоследнего ключа до последнего
 
 идея возникшая утром - проверять сначала открытый путь до от ст до фш, затем блокировать двери и проделать тоже самое, в конце сверить длину пройденных путей и выбрать оптимальный
 
 для этого надо добавить проверку дверь/не дверь в АСтар функции при проходе соседей
 
 при поиске путей от ключа до ключа/двери, так же проверять вариант с дверьми / без, выбирать кратчайший
 
 
 */



























