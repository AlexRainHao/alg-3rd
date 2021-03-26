//
// Created by AlexRain on 2021/2/14.
//

#ifndef PRACTICE_STACK_H
#define PRACTICE_STACK_H

#include "Vector.h"

template<typename T>
class Stack:public Vector<T>{
public:
    Stack(T const *arr, Rank n){
        this->copyFrom(arr, 0, n);
    }
    Stack():Vector<T>(){};

    void push(T const &e){
        this->insert(this->size(), e);
    }
    T pop(){
        return (this->size() - 1);
    }
    T& top(){
        return (*this)[this->size() - 1];
    }
};

#endif //PRACTICE_STACK_H
