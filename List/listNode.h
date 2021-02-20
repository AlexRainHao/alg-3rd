//
// Created by AlexRain on 2021/2/11.
//

#ifndef PRACTICE_LISTNODE_H
#define PRACTICE_LISTNODE_H

#define ListNodePosi(T) ListNode<T>*

template <typename T>
struct ListNode{
    T data;
    ListNodePosi(T) pred;
    ListNodePosi(T) succ;

    ListNode(){};
    ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr):
        data(e), pred(p), succ(s){};
    ListNodePosi(T) insertAfter(T const &e);
    ListNodePosi(T) insertPred(T const &e);
};

template<typename T>
ListNodePosi(T) ListNode<T>::insertAfter(const T &e) {
    ListNodePosi(T) p = new ListNode(e, this, succ);
    succ->pred = p;
    succ = p;
    return p;
}

template<typename T>
ListNodePosi(T) ListNode<T>::insertPred(const T &e) {
    ListNodePosi(T) p = new ListNode(e, pred, this);
    pred->succ = p;
    pred = p;
    return p;
}
#endif //PRACTICE_LISTNODE_H
