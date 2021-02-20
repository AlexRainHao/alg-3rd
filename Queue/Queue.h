//
// Created by AlexRain on 2021/2/20.
//

#ifndef PRACTICE_QUEEN_H
#define PRACTICE_QUEEN_H

#include "List.h"

template<typename T>
class Queue : public List<T> {
public:
    Queue(T const *arr, Rank n);
    Queue():List<T>(){};
    void enqueue(T const &e) { this->insertTail(e); }
    T dequeue() { return this->remove(this->first()); }
    T& front(){ return this->first()->data; }
};

template <typename T>
Queue<T>::Queue(T const *arr, Rank n): List<T>(){
    for (int i = 0; i < n; i++)
        this->insertTail(*(arr + i));
};

#endif //PRACTICE_QUEEN_H

