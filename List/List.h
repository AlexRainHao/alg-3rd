//
// Created by AlexRain on 2021/2/11.
//

#ifndef PRACTICE_LIST_H
#define PRACTICE_LIST_H

#include "listNode.h"

typedef int Rank;


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
        return p->succ != nullptr;

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
    void sort(ListNodePosi(T) p, int n); // sort for span of [p, p+n]
    void sort(){
        return sort(first(), _size);
    }

    int deduplicate();
    int uniquify(); // for ordered one

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
T& List<T>::operator[](Rank r) const{
    ListNodePosi(T) p = first();
    while (0 < r--){
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


template<typename T>
T List<T>::remove(ListNodePosi(T) p){
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    T e = p->data;
    delete p;
    _size--;
    return e;

}

template<typename T>
int List<T>::clear(){
    int oldSize = _size;
    while(_size > 0)
        remove(header->succ);
    return oldSize;
}

template<typename T>
List<T>::~List(){
    clear();
    delete header;
    delete tailer;
}

template<typename T>
int List<T>::deduplicate(){
    if (_size < 2) return 0;

    int oldSize = _size;
    ListNodePosi(T) p = header;
    Rank r = 0;

    while(isvalid(p = p->succ)){
        ListNodePosi(T) q = find(p->data, r, p);
        q ? remove(q): r++;
    }
    return oldSize - _size;
}

template<typename T>
void List<T>::traverse(void (*visit)(T &)) {
    ListNodePosi(T) p = header->succ;

    while(isvalid(p)){
        visit(p->data);
        p = p->succ;
    }
}

template<typename T>
template<typename VST>
void List<T>::traverse(VST &visit) {
    ListNodePosi(T) p = header->succ;
    while(isvalid(p)){
        visit(p->data);
        p = p->succ;
    }
}

template<typename T>
int List<T>::uniquify() {
    if (_size < 2) return 0;

    int oldSize = _size;
    ListNodePosi(T) p = header->succ;
    int e = p->data;

    while(isvalid(p = p->succ)){
        if (p->data == e) {
            ListNodePosi(T) q = p;
            remove(p);
            p = q->succ;
        }
        else
            e = p->data;
    }

    return oldSize - _size;
}

template <typename T>
ListNodePosi(T) List<T>::search(T const &e, int n, ListNodePosi(T) p) const{
    while(0 < n--){
        if (((p = p->pred)->data <= e)) break;
    }
    return p;
}

template<typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n){
    ListNodePosi(T) max = p;
    for(int i = 0; i < n; i++){
        if (p->data > max->data)
            max = p;
        p = p->succ;
    }
    return max;
}

template<typename T>
void List<T>::sort(ListNodePosi(T) p, int n){
    switch(rand() % 1){
        case 1: insertionSort(p, n); break;
        case 2: selectionSort(p, n); break;
        default: mergeSort(p, n); break;
    }
}

template<typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n){
    for (int i = 0; i < n; i++){
        p->data;
        insertAfter(search(p->data, i, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template<typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n){
    ListNodePosi(T) head = p->pred;
    ListNodePosi(T) tail = p;
    for(int i = 0; i < n; i++)
        tail = tail->succ;

    while(1 < n){
        ListNodePosi(T) max = selectMax(head->succ, n);
        insertBefore(tail, remove(max));
        tail = tail->pred;
        n--;
    }
}

template<typename T>
void List<T>::merge(ListNodePosi(T) &p, int n, List<T> &L, ListNodePosi(T) q, int m) {
    // merge [p, p+n] to [q, q+m] of L
    ListNodePosi(T) pp = p->pred;

    while(m > 0){
        if ((n > 0) && (p->data <= q->data)){
            if (q == (p = p->succ)) break;
            n--;
        }
        else{
            insertBefore(p, L.remove((q = q->succ)->pred));
            m--;
        }
    }
    p = pp->succ;
}

template<typename T>
void List<T>::mergeSort(ListNodePosi(T) &p, int n) {
    if (n < 2) return;

    Rank mi = n >> 1;
    ListNodePosi(T) q = p;
    for (int i = 0; i < mi; i++)
        q = q->succ;

    mergeSort(p, mi);
    mergeSort(q, n - mi);
    merge(p, mi, *this, q, n - mi);
}

template<typename T>
int List<T>::disordered() const {
    int n = 0;
    ListNodePosi(T) p = header->succ;
    for (int i = 1; i < _size; i++){
        if (p->data > p->succ->data)
            n++;
    }
    return n;
}

//template<typename T>
//void List<T>::reverse(){
//    for (auto p = header; p; p = p->pred)
//        std::swap(p->pred, p->succ);
//    std::swap(header, tailer);
//}

template<typename T>
void List<T>::reverse(){
    ListNodePosi(T) p = header;
    ListNodePosi(T) q = tailer;

    for (int i = 1; i < _size; i += 2)
        std::swap((p = p->succ)->data, (q = q->pred)->data);
}

#endif //PRACTICE_LIST_H
