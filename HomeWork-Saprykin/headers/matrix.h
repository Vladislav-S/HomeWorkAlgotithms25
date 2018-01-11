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
using namespace std;

template <typename A>
class matrix{
private:
    size_t m{0};
    size_t n{0};
    vector<shared_ptr<vector<A>>> v;
    void countWidth();
    void print();
public:
    matrix(); /// для пустой матрицы
    matrix(int mm); /// для создание неровной матрицы
    matrix(int m, int n); /// для создания матрицы размером m*n
    matrix(const matrix<A> & mtr); ///конструктор копирования
    void increase_row(); ///добавление строки
    void push_back(A val); ///добавить элемент в конец последней строки
    void push_back(shared_ptr<vector<A>>); ///добавить целую строку
    void Print(); ///печать матрицы
    vector<A> & operator[] (size_t _m) const; ///получение элемента по индексу
    size_t h() const; ///высота матрицы (m)
    size_t w() const; ///ширина матрицы (n)
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
    m = _m;
    n = _n;
}

template<typename A>
matrix<A>::matrix(const matrix<A> & mtr){
    for(auto i{0}; i < mtr.h(); i++){
        v.push_back(make_shared<vector<A>>(mtr.w()));
    }
    for(auto _m{0}; _m < mtr.h(); _m++){
        for(auto _n{0}; _n < mtr.w(); _n++){
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
            cout << b << " ";
        }
        cout << endl;
    }
}
template <typename A>
void matrix<A>::Print(){
    print(); // analog
}

template <typename A>
vector<A> & matrix<A>::operator[] (size_t _m) const{
    if(_m < 0 || _m > v.size()-1) throw out_of_range("wrong matrix [index]");
    return *v.at(_m).get();
}

template <typename A>
size_t matrix<A>::h() const { //m
    return v.size();
}

template <typename A>
size_t matrix<A>::w() const { //n
    return n;
}

template <typename A>
void matrix<A>::countWidth(){
    size_t min = v.at(0).get()->size();
    for(auto a : v){
        if(min > a.get()->size()) min = a.get()->size();
    }
    n=min;
}

#endif /* matrix_h */
