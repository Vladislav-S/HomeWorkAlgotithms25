//
//  map.cpp
//  HomeWork-Saprykin
//
//  Created by Vlad Saprykin on 26.11.2017.
//  Copyright © 2017 Vlad Saprykin. All rights reserved.
//

#include "headers/map.h"

bool operator==(const shared_ptr<Point> & l, const shared_ptr<Point> & r){
    return l.get()->m == r.get()->m && l.get()->n == r.get()->n;
}

Map::Map(int ac, char * av[]){
    argc = ac;
    argv = av;
}

bool Map::out_of_range(size_t _m, size_t _n){
    if(_m >= M.h()){
        return true;
    }else if (_n >= M.w()){
        return true;
    }
    return false;
}

vector<shared_ptr<Point>> Map::Neighbors(const shared_ptr<Point> &p){
    vector<shared_ptr<Point>> v;
    Cords base(p.get()->m, p.get()->n);
    //че там сверху
    if(!out_of_range(base.first-1, base.second)){
        if(
           M[base.first-1][base.second][0] != symbols[7] && //d
           M[base.first-1][base.second][0] != symbols[2]){ //#
            v.push_back(make_shared<Point>(Cords(base.first-1, base.second)));
        }
    }
    
    //че там снизу
    if(!out_of_range(base.first+1, base.second)){
        if(M[base.first+1][base.second][0] != symbols[5] && //u
           M[base.first+1][base.second][0] != symbols[2]){
            v.push_back(make_shared<Point>(Cords(base.first+1, base.second)));
        }
    }

    //че там слева
    if(!out_of_range(base.first, base.second-1)){
        if(M[base.first][base.second-1][0] != symbols[6] &&
           M[base.first][base.second-1][0] != symbols[2]){
            v.push_back(make_shared<Point>(Cords(base.first, base.second-1)));
        }
    }

    //че там справа
    if(!out_of_range(base.first, base.second+1)){
        if(M[base.first][base.second+1][0] != symbols[8] &&
           M[base.first][base.second+1][0] != symbols[2]){
            v.push_back(make_shared<Point>(Cords(base.first, base.second+1)));
        }
    }
    return v;
}
void Map::start(){
    //Парсим файл в матрицу
    //cout << symbols[1];

    if(argc == 1){
        parse_file((char *)"map.txt");
    }
    else{
        parse_file(argv[1]);
    }
}

void Map::start(int ac, char * av[]){
    argc = ac;
    argv = av;
    start();
}

void Map::parse_file(char * c){
    string filename{c};
    fstream fstr(filename);
    
    if(!fstr.is_open()){
        throw my_exception("error with file (no such file in directory)");
    }else{
        char ch2;
        string temp;
        while(!fstr.eof()){
            
            fstr.get(ch2);
            if(fstr.eof()){
                M.push_back(temp);
                break;
            }
            
            
            // 4 - '*' 3 - '@' 2 - '#' 1 - '
            if(ch2 == symbols[0]){ // 0 - '\n'
                M.push_back(temp);

                M.increase_row();
                temp = "";
            }else if(ch2 == ','){
                M.push_back(temp);
                temp = "";
            }
            else if(strchr(symbols, ch2) != nullptr){
                temp += string(sizeof(char), ch2);
            }
            else{
                throw my_exception("bad symbol in text file"); //todo : throw ошибку - done
                return;
            }
            
        }
        fstr.close();
        //cout << M[1][1][0] << endl;
    }
}



shared_ptr<Point> Map::whereIsHeroSymbol(){
    for(int i{0}; i < M.h(); i++){
        for(int j{0}; j < M.w(); j++){
            if(M[i][j][0] == symbols[3]) return make_shared<Point>(Cords(i, j));
            //cout << "found " << i << " " << j << endl; //DEBUG

        }
    }
    throw my_exception("no hero symbol found, check your Map");
}

shared_ptr<Point> Map::whereIsExitSymbol(){
    for(int i{0}; i < M.h(); i++){
        for(int j{0}; j < M.w(); j++){
            if(M[i][j][0] == symbols[4]) return make_shared<Point>(Cords(i, j));
            //cout << "found " << i << " " << j << endl; //DEBUG
        }
    }
    throw my_exception("no exit symbol found, check your Map");
}

bool Map::isDoor(const shared_ptr<Point> & p){
    if(out_of_range(p.get()->m, p.get()->n)) throw my_exception("Point is out of range");
    if(M[p.get()->m][p.get()->n][0] == symbols[9]) return true;
    return false;
}
bool Map::isKey(const shared_ptr<Point> & p){
    if(out_of_range(p.get()->m, p.get()->n)) throw my_exception("Point is out of range");
    if(M[p.get()->m][p.get()->n][0] == symbols[10]) return true;
    return false;
}

//DANGER - неизвестное поведение объектов указателя
shared_ptr<Point> Map::whereIsSymbol(const shared_ptr<Point> & p){
    auto pos = M[p.get()->m][p.get()->n].find("D");
    string dIndex = M[p.get()->m][p.get()->n].substr(pos);
    //string dIndex = M[p.get()->m][p.get()->n].substr(1, M[p.get()->m][p.get->n].size()-2);
    for(auto i{0}; i < M.h(); i++){
        for(auto j{0}; j < M.w(); j++){
            if(M[i][j].substr(M[i][j].find("k")) == dIndex){
                return shared_ptr<Point>(make_shared<Point>(i, j));
            }
        }
    }
    
    return shared_ptr<Point>();
}

vector<shared_ptr<Point>> Map::whereIsSymbols(const shared_ptr<Point> & p){
    vector<shared_ptr<Point>> v;
    auto pos = M[p.get()->m][p.get()->n].find("D");
    string dIndex = M[p.get()->m][p.get()->n].substr(pos+1);
    //string dIndex = M[p.get()->m][p.get()->n].substr(1, M[p.get()->m][p.get->n].size()-2);
    for(auto i{0}; i < M.h(); i++){
        for(auto j{0}; j < M.w(); j++){
            if(M[i][j].substr(M[i][j].find("k")+1) == dIndex){
                v.push_back(make_shared<Point>(i, j));
            }
        }
    }
    return v;
}

bool Map::isKeyForDoor(const shared_ptr<Point> & k, const shared_ptr<Point> & d){
    Point key(k.get()->m, k.get()->n);
    Point door(d.get()->m, d.get()->n);
    if(M[key.m][key.n].substr(M[key.m][key.n].find("k")+1) == M[door.m][door.n].substr(M[door.m][door.n].find("D")+1)) return true;
    return false;
}
