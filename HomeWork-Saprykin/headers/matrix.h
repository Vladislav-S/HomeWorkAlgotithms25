//
//  matrix.h
//  HomeWork-Saprykin
//
//  Created by Vlad Saprykin on 26.11.2017.
//  Copyright © 2017 Vlad Saprykin. All rights reserved.
//

#ifndef matrix_h
#define matrix_h
#include "base.h"
#pragma once
using namespace std;

template <typename A>
class matrix{
private:
    int m{0};
    int n{0};
    vector<shared_ptr<vector<A>>> v;
    void countWidth();
public:
    matrix(); // для пустой матрицы
    matrix(int mm); // для создание неровной матрицы
    matrix(int m, int n); // для создания матрицы размером m*n
    matrix(const matrix<A> & mtr);
    void increase_row(); //добавление строки
    void push_back(A val);
    void push_back(shared_ptr<vector<A>>);
    void print();
    void Print();
    void make_default();
    void makeMN(int m, int n);
    A getElemByCords(int _m, int _n) const; //получить указатель на элемент по координатам (от нуля)
    vector<A> & operator[] (int _m) const;
    //todo: operator=
    int h() const;
    int w() const;
    //туду: стандартный конструктор для ровной матрицы
};

template <typename A>
matrix<A>::matrix(){
    increase_row();  //вылезла ошибка - upd: испугалась и спряталась
}

template <typename A>
matrix<A>::matrix(int mm){
    for(auto i{0}; i < mm; i++){
        increase_row();
    }
    //m--; // уровнять //upd - число а не индекс строки
}

template<typename A>
matrix<A>::matrix(int _m, int _n){
    for(auto i{0}; i<_m; i++){
        increase_row();
        v.at(i).get()->resize(_n);
    }
    m = _m; //todo: убрать избыточность
    n = _n;
}

template<typename A>
matrix<A>::matrix(const matrix<A> & mtr){
    for(auto i{0}; i < mtr.h(); i++){
        v.push_back(make_shared<vector<A>>(mtr.w()));
    }
    for(auto _m{0}; _m < mtr.h(); _m++){
        for(auto _n{0}; _n < mtr.w(); _n++){
            //this[_m][_n] = mtr[_m][_n];
            v.at(_m).get()->at(_n) = mtr.getElemByCords(_m, _n);
        }
    }
    
}

template <typename A>
void matrix<A>::increase_row(){
    v.push_back(make_shared<vector<A>>());
    m++;
}

template <typename A>
void matrix<A>::push_back(A val){
    v.at(m-1).get()->push_back(val);
    countWidth();
    
}

template <typename A>
void matrix<A>::push_back(shared_ptr<vector<A>> val){
    v.push_back(val);
    countWidth();
}

template <typename A>
void matrix<A>::print(){
    for(auto a : v){
        for(auto b : *a.get()){
            if(typeid(A) == typeid(wchar_t)){
                wcout << b << " ";
            }
            else{
                cout << b << " ";
            }
        }
        cout << endl;
    }
}
template <typename A>
void matrix<A>::Print(){
    print(); // analog
}

template <typename A> //todo : протестить
void matrix<A>::make_default(){
    for(auto a : v){
        a.get()->clear();
        a.get()->resize(n);
    }
}

template <typename A>
void matrix<A>::makeMN(int _m, int _n){
    v.clear();
    m, n = 0; //todo: убрать избыточность
    for(auto i{0}; i<_m; i++){
        increase_row();
        v.at(i).get()->resize(_n);
    }
    m = _m;
    n = _n;
}

template <typename A>
A matrix<A>::getElemByCords(int _m, int _n) const{
    return v.at(_m).get()->at(_n);
}

template <typename A>
vector<A> & matrix<A>::operator[] (int _m) const{
    if(_m < 0 || _m > v.size()-1) throw "wrong array param";
    return *v.at(_m).get();
}

template <typename A>
int matrix<A>::h() const { //m
    return v.size();
}

template <typename A>
int matrix<A>::w() const { //n
    return n;
}

template <typename A>
void matrix<A>::countWidth(){ //на всякий случай ищем длину самого короткого вектора (хотя по идее надо выровнять матрицу)
    int min = v.at(0).get()->size();
    for(auto a : v){
        if(min > a.get()->size()) min = a.get()->size();
    }
    n=min;
}

#endif /* matrix_h */
