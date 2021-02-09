//
// Created by AlexRain on 2021/2/7.
//

#ifndef PRACTICE_VECTOR_H
#define PRACTICE_VECTOR_H

typedef int Rank;
#define DEFAULT_CAPACITY 3

#include "fibonacci.h"
#include <iostream>

//using namespace std;

template <typename T>
class Vector {
protected:
    Rank _size;
    int _capacity;
    T *_elem;

    void copyFrom(T const *A, Rank lo, Rank hi); // copy from span [lo, hi]

    void expand();

    void shrink();

    bool bubble(Rank lo, Rank hi);

    void bubbleSort(Rank lo, Rank hi);

    void selectionSort(Rank lo, Rank hi);

    void merge(Rank lo, Rank mi, Rank hi);

    void mergeSort(Rank lo, Rank hi);

//    void heapSort(Rank lo, Rank hi);
//
//    void quickSort(Rank lo, Rank hi);
//
//    Rank max(Rank lo, Rank hi);
//
//    Rank partition(Rank lo, Rank hi);

public:
    // series of constructor
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
        c = c < s ? s: c;
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    }
    Vector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
    Vector(T const *A, Rank n) { copyFrom(A, 0, n); }
    Vector(Vector<T> const &V, Rank lo, Rank hi) {
        copyFrom(V._elem, lo, hi);
    }
    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); }
    Vector<T>& operator=(Vector<T> const &V);

    // de-constructor
    ~Vector() { delete[] _elem; }

    // apis
    T& operator[](Rank r) const;

    Rank size() const { return _size; }
    Rank capacity() const { return _capacity;}
    bool empty() const {return !_size;}

    int disordered() const; // number of elements that not disordered
    Rank find(T const &e, Rank lo, Rank hi) const; // find from span [lo, hi)
    Rank find(T const &e) const { return find(e, 0, _size); }

    Rank search(T const &e, Rank lo, Rank hi) const;
    Rank search(T const &e) const{
        return (0 >= _size) ? -1: search(e, 0, _size);
    }

    T remove(Rank r); // remove single element
    int remove(Rank lo, Rank hi); // remove span of elements [lo, hi)

    Rank insert(Rank r, T const &e);
    Rank insert(T const &e){ return insert(_size, e); }

    void sort(Rank lo, Rank hi);
    void sort() {sort(0, _size);}

    void unsort(Rank lo, Rank hi); // permute for span of [lo, hi)
    void unsort(){ unsort(0, _size); }
    void permute(Vector<T> &V);

    int deduplicate(); // unify for disordered one
    int uniquify(); // unify for ordered one

    void traverse(void (*visit)(T&)); // where visit is a pointer to function
    template <typename VST> void traverse(VST &visit); // where visit is a function, and visit() may reloaded

};

template <typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 *(hi - lo)];
    _size = 0;

    while(lo < hi)
        _elem[_size++] = A[lo++];
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &V) {
    if (_elem) delete[] _elem;
    copyFrom(V._elem, 0, V.size());
    return *this;
}

template <typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return;
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;

    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];

    for(int i = 0; i < _size; i++)
        oldElem[i] = _elem[i];

    delete [] oldElem;
}

template <typename T>
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1) return;
    if (_size << 2 > _capacity) return;

    T* oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; i++){
        _elem[i] = oldElem[i];
    }

    delete [] oldElem;
}

template <typename T>
T& Vector<T>::operator[](Rank r) const {
    return _elem[r];
}

template <typename T>
void Vector<T>::permute(Vector<T> &V) {
    for (int i = _size; i > 0; i--)
        std::swap(V[i - 1], V[rand() % i]);
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi){
    Rank span = hi - lo;
    T* spanV = _elem + lo;
    for (int i = span; i > 0; i--)
        std::swap(spanV[i - 1], spanV[rand() % i]);
}

template <typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const {
    while ((lo < hi--) && (e == _elem[hi]))
        return hi;
    return -1;
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const &e){
    expand();

    for (int i = _size; i > r; i--)
        _elem[i] = _elem[i - 1];
    _elem[r] = e;

    return r;
}

template <typename T>
T Vector<T>::remove(Rank r) {
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    if (lo == hi || lo > _size - 1) return 0;

    while (hi < _size)
        _elem[lo++] = _elem[hi++];

    _size = lo;
    shrink();
    return hi - lo;
}

template <typename T>
int Vector<T>::deduplicate() {
    int oldSize = _size;
    Rank i = 1;
    while (i < _size)
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);

    return oldSize - _size;
}

template <typename T>
void Vector<T>::traverse(void (*visit)(T &)) {
    for(int i = 0; i < _size; i++)
        visit(_elem[i]);
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST &visit) {
    for (int i = 0; i < _size; i++)
        visit(_elem[i]);
}

template <typename T>
int Vector<T>::disordered() const {
    int n = 0;
    for (int i = 1; i < _size; i++)
        if (_elem[i - 1] > _elem[i]) n++;
    return n;
}

template <typename T>
int Vector<T>::uniquify() {
    Rank i = 0, j = 0;
    while(++j < _size){
        if (_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    }
    _size = ++i;
    shrink();
    return j - i;
}

template <typename T>
static Rank binSearch(T *A, const T &e, Rank lo, Rank hi){
    while (lo < hi){
        Rank mi = (lo + hi) >> 1;
        if (e < A[mi]) hi = mi;
        else if (e > A[mi]) lo = mi;
        else return mi;
    }
    return -1;
}

template <typename T>
static Rank binSearchB(T *A, const T &e, Rank lo, Rank hi){
    while (lo < hi){
        Rank mi = (lo + hi) >> 1;
        A[mi] > e ? hi = mi: lo = mi + 1;
    }
    return --lo;
}

template <typename T>
static Rank fibSearch(T *A, const T &e, Rank lo, Rank hi){
    Fib fib(hi - lo);
    while (lo < hi){
        while (hi - lo < fib.get()) fib.prev();
        Rank mi = lo + fib.get() - 1;

        if (e < A[mi]) hi = mi;
        else if (e > A[mi]) lo = mi;
        else return mi;
    }
    return -1;
}

template <typename T>
Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const {
    return (rand() % 2) ?
        binSearch(_elem, e, lo, hi): fibSearch(_elem, e, lo ,hi);
}

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi){
    switch (rand() % 3){
//        case 1: bubbleSort(lo, hi); break;
//        case 2: selectionSort(lo, hi); break;
//        case 3: mergeSort(lo, hi); break;
//        case 4: heapSort(lo, hi); break;
//        default: quickSort(lo, hi); break;
        case 1: bubbleSort(lo, hi); break;
        case 2: selectionSort(lo, hi); break;
        default: mergeSort(lo, hi); break;
    }
}

/* Series of normal Sorting Algorithm */
template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi){
    bool sorted = true;

    while (++lo < hi)
        if (_elem[lo - 1] > _elem[lo]) {
            sorted = false;
            std::swap(_elem[lo - 1], _elem[lo]);
        }

    return sorted;
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
    while (!bubble(lo, hi--));
}

template <typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi){
    /* select the minimum element insert to head position */
    while (lo < hi){
        int min_index = lo;
        for (int i = lo; i < hi; i++)
            if (_elem[i] < _elem[min_index])
                min_index = i;

        std::swap(_elem[lo], _elem[min_index]);
        lo++;
    }
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T *A = _elem + lo;

    // for first part
    int lb = mi - lo;
    T *B = new T[lb];
    for (Rank i = 0; i < lb; i++)
        B[i] = A[i];

    //for second part
    int lc = hi - mi;
    T *C = _elem + mi;

    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);){
        if ((j < lb) && (!(k < lc) || (B[j] <= C[k]))) A[i++] = B[j++];
        if ((k < lc) && (!(j < lb) || (C[k] < B[j])))A[i++] = C[k++];
    }

    delete [] B;
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if (hi - lo < 2) return;

    Rank mi = (hi + lo) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

#endif //PRACTICE_VECTOR_H
