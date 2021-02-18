//
// Created by yyh on 2021/2/9.
//

#ifndef PRACTICE_LIST_H
#define PRACTICE_LIST_H

#include "ListNode.h"

template <typename T>
class List{
private:
    int _size;
    ListNodePosi(T) header; ListNodePosi(T) tailer;

protected:
    void init();
    void clear();
    void copyNodes(ListNodePosi(T) L, int n);

    void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);
    void mergeSort(ListNodePosi(T)&, int);
    void selectionSort(ListNodePosi(T), int);
    void insertionSort(ListNodePosi(T), int);

public:
    // series of constructor
    List() {init();}
    List(List<T> const &L);
    List(List<T> const &L, Rank lo, Rank hi);
    List(ListNodePosi(T) p, int n);

    // de-constructor
    ~List();

    // series of API for read only
    Rank size() const {return _size;}
    bool empty() const {return _size <= 0;}

    T& operator[](Rank r) const;
    ListNodePosi(T) head() const {return header->succ;}
    ListNodePosi(T) tail() const {return tailer->prev;}
    bool valid(ListNodePosi(T) p){
        return p && tailer != p && header != p;
    }

    int disordered() const;

    ListNodePosi(T) find(T const &e, Rank n ,ListNodePosi(T) p) const; // find from span [p-n, p] for unsorted one
    ListNodePosi(T) find(T const &e) const{
        return find(e, _size, tailer);
    }
    ListNodePosi(T) search(T const &e, Rank n ,ListNodePosi(T) p) const; // find from span [p-n, p] for sorted one
    ListNodePosi(T) search(T const &e) const{
        return find(e, _size, tailer);
    }
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
    ListNodePosi(T) selectMax(){ return selectMax(header->succ, _size); }

    // series of API allows write
    ListNodePosi(T) insertAsFirst(T const &e);
    ListNodePosi(T) insertAsLast(T const &e);
    ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const &e);
    ListNodePosi(T) insertAfter(ListNodePosi(T)p, T const &e);

    T remove(ListNodePosi(T) p);

    void merge(List<T>& L){
        merge(head(), size, L, L.head(), L._size);
    }
    void sort(ListNodePosi(T) p, int n);
    void sort(){ return sort(head(), _size); }

    int deduplicate(); // unify for unsorted one
    int uniquify(); // unify for sorted one
    void reverse();

    void traverse(void (*)(T&))
    template<typename VST> void traverse(VST&);
};

#endif //PRACTICE_LIST_H
