//
// Created by AlexRain on 2021/2/11.
//

#ifndef PRACTICE_LIST_H
#define PRACTICE_LIST_H

#include "listNode.h"

template <typename T>
class List{
private:
    int _size;
    ListNodePosi(T) header;
    ListNodePosi(T) tailer;

protected:
    void init();
    int clear();
    void copyNodes(ListNodePosi(T) p, int n); // copy n elements start from p;
    void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);
    void mergeSort(ListNodePosi(T)&, int);
    void selectionSort(ListNodePosi(T), int);
    void insertionSort(ListNodePosi(T), int);

public:
    // a series of constructor
    List(){init();};
    List(List<T> const &L);
    List(List<T> const &L, Rank r, int n);
    List(ListNodePosi(T) p, int n);

    ~List();

    Rank size() const { return _size; }
    bool empty() const { return _size <= 0; }

    T& operator[](Rank r) const;

    ListNodePosi(T) first() const {return header->succ; }
    ListNodePosi(T) last() const { return tailer->pred;}
    bool valid(ListNodePosi(T) p){
        return p && header != p && tailer != p;
    }

    bool isvalid(ListNodePosi(T) p){
        if (p == nullptr) return false;
        if (p->succ == nullptr) return false;

        return true;
    }

    int disordered() const;

    ListNodePosi(T) find(T const &e, int n, ListNodePosi(T) p) const;
    ListNodePosi(T) find(T const &e) const{
        return find(e, _size, tailer);
    }
    ListNodePosi(T) search(T const &e, int n, ListNodePosi(T) p) const;
    ListNodePosi(T) search(T const &e) const{
        return search(e, _size, tailer);
    }

    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
    ListNodePosi(T) selectMax(){
        return selectMax(header->succ, _size);
    };

    ListNodePosi(T) insertHead(T const &e);
    ListNodePosi(T) insertTail(T const &e);
    ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const &e);
    ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const &e);

    T remove(ListNodePosi(T) p);

    void merge(List<T> &L){
        merge(first(), _size, L, L.first(), L._size);
    }
    void sort(ListNodePosi(T) p, int n);
    void sort(){
        return sort(first(), _size);
    }

    int deduplicate();
    int uniquify();

    void reverse();

    void traverse(void(*visit)(T&));
    template <typename VST> void traverse(VST &visit);
};


// ========================
template<typename T>
void List<T>::init(){
    header = new ListNode<T>;
    tailer = new ListNode<T>;
    header->succ = tailer; header->pred = nullptr;
    tailer->pred = header; tailer->succ = nullptr;
    _size = 0;
}

template<typename T>
T List<T>::operator[](Rank r) const{
    ListNodePosi(T) p = first();
    while (0 > r--){
        p = p->succ;
    }
    return p->data;
}

template<typename T>
ListNodePosi(T) List<T>::find(const T &e, int n, ListNode<T> *p) const {
    while(n--){
        if (e == (p = p->pred)->data)
            return p;
    }
    return nullptr;
}

template<typename T>
ListNodePosi(T) List<T>::insertHead(const T &e) {
    _size++;
    return header->insertAfter(e);
}

template<typename T>
ListNodePosi(T) List<T>::insertTail(const T &e) {
    _size++;
    return tailer->insertPred(e);
}

template<typename T>
ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, const T &e) {
    _size++;
    return p->insertAfter(e);
}

template<typename T>
ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, const T &e) {
    _size++;
    return p->insertPred(e);
}

template<typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n) {
    init();
    while(n-- && isvalid(p)){
        insertTail(p->data);
        p = p->succ;
    }
}

template<typename T>
List<T>::List(const List<T> &L) {
    copyNodes(L.first(), L.size());
}

template<typename T>
List<T>::List(List<T> const &L, Rank r, int n){
    copyNodes(L[r], n);
}


template<typename T>
List<T>::List(ListNodePosi(T) p, int n){
    copyNodes(p, n);
}


#endif //PRACTICE_LIST_H
