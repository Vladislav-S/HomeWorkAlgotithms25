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

bool Map::out_of_range(int _m, int _n){
    if(_m >= m.h()){
        return true;
    }else if (_m < 0){
        return true;
    }else if (_n >= m.w()){
        return true;
    }else if (_n < 0){
        return true;
    }
    return false;
}

vector<shared_ptr<Point>> Map::Neighbors(shared_ptr<Point> p){
    //добавить на выход за границы
    vector<shared_ptr<Point>> v;
    Cords base(p.get()->m, p.get()->n); //у меня n*m или наоборот?
    //че там сверху
    if(!out_of_range(base.first-1, base.second)){
        if(
           m[base.first-1][base.second] != symbols[7] && //d
           m[base.first-1][base.second] != symbols[2]){ //#
            v.push_back(make_shared<Point>(Cords(base.first-1, base.second)));
        }
    }
    
    //че там снизу
    if(!out_of_range(base.first+1, base.second)){
        if(m[base.first+1][base.second] != symbols[5] && //u
           m[base.first+1][base.second] != symbols[2]){
            v.push_back(make_shared<Point>(Cords(base.first+1, base.second)));
        }
    }

    //че там слева
    if(!out_of_range(base.first, base.second-1)){
        if(m[base.first][base.second-1] != symbols[6] &&
           m[base.first][base.second-1] != symbols[2]){
            v.push_back(make_shared<Point>(Cords(base.first, base.second-1)));
        }
    }

    //че там справа
    if(!out_of_range(base.first, base.second+1)){
        if(m[base.first][base.second+1] != symbols[8] &&
           m[base.first][base.second+1] != symbols[2]){
            v.push_back(make_shared<Point>(Cords(base.first, base.second+1)));
        }
    }
    return v;
}
void Map::start(){
    if(argc == 0 || argv == nullptr){ //невозможно
        throw invalid_argument("error with params in Map(argc, argv)");
    }
    
    //Парсим файл в матрицу
    if((argc == 2 && (argv[1] == "")) || argc == 1){ //todo: сделать проверку нормально
        parse_file((char *)"map.txt");
    }
    else{
        parse_file(argv[1]);
    }
    
    m1.makeMN(m.h(), m.w());
    //m1[0][0] = true;
    //m1.print();
    
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
        cout << "error with opening" << endl;
    }else{
        char ch2;
        while(!fstr.eof()){
            
            fstr.get(ch2);
            if(fstr.eof()) break; //выскакивал какой-то ссаный символ в конце, починил d
            
            // 4 - '*' 3 - '@' 2 - '#' 1 - ' '
            if(ch2 == symbols[1]
               || ch2 == symbols[2]
               || ch2 == symbols[3]
               || ch2 == symbols[4]
               || ch2 == symbols[5]
               || ch2 == symbols[6]
               || ch2 == symbols[7]
               || ch2 == symbols[8]
               || ch2 == symbols[9]
               || ch2 == symbols[10]){
                m.push_back(ch2);
            }
            else if(ch2 == symbols[0]){ // 0 - '\n'
                m.increase_row();
            }
            else{
                throw "bad symbol in text file"; //todo : throw ошибку - done
                return;
            }
            
        }
        //m.print(); //todo: должно быть выключено в релизе
        fstr.close();
    }
}



shared_ptr<Point> Map::whereIsHeroSymbol(){ //где символ героя todo: переделать для любого символа
    for(int i{0}; i < m.h(); i++){
        for(int j{0}; j < m.w(); j++){
            if(m[i][j] == symbols[3]) return make_shared<Point>(Cords(i, j));
        }
    }
    throw "no hero symbol found, check your Map";
}

shared_ptr<Point> Map::whereIsExitSymbol(){ //где символ героя todo: переделать для любого символа
    for(int i{0}; i < m.h(); i++){
        for(int j{0}; j < m.w(); j++){
            if(m[i][j] == symbols[4]) return make_shared<Point>(Cords(i, j));
        }
    }
    throw "no exit symbol found, check your Map";
}

bool Map::isDoor(const shared_ptr<Point> & p){
    if(out_of_range(p.get()->m, p.get()->n)) throw; //out of range;
    if(m[p.get()->m][p.get()->n] == symbols[9]) return true;
    return false;
}
bool Map::isKey(const shared_ptr<Point> & p){
    if(out_of_range(p.get()->m, p.get()->n)) throw; //out of range;
    if(m[p.get()->m][p.get()->n] == symbols[10]) return true;
    return false;
}
//TODO: сжедать интерфейс для работы с матрицей
