//
// Created by yyh on 2021/4/4.
//

#ifndef PRACTICE_SEARCHTREE_H
#define PRACTICE_SEARCHTREE_H

#include "BinTree.h"

template <typename T>
class BST: public BinTree<T>{
protected:
    BinNodePosi(T) _hot;
    BinNodePosi(T) connect34(
            BinNodePosi(T), BinNodePosi(T),BinNodePosi(T),
            BinNodePosi(T),BinNodePosi(T),BinNodePosi(T),BinNodePosi(T));
    BinNodePosi(T) retateAt(BinNodePosi(T));

public:
    virtual BinNodePosi(T)& search(const T&);
    virtual BinNodePosi(T) insert(const T&);
    virtual bool remove(const T&);
};

template<typename T>
static BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot){
    if (!v || e == v->data) return v;
    hot = v;
    return searchIn(((e < v->data) ? v->lChild : v->rChild), e, hot);
}

template<typename T>
BinNode<T> *&BST<T>::search(const T &e) {
    return searchIn(_root, e, _hot = nullptr);
}

template<typename T>
BinNode<T> *BST<T>::insert(const T &e) {
    BinNodePosi(T) &x = search(e); if (x) return x;
    x = new BinNode<T>(e, _hot);
    _size++;
    updateHeightAbove(x);
    return x;
}

template<typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot){
    BinNodePosi(T) w = x;
    BinNodePosi(T) succ = nullptr;

    if (!HasLChild(*x))
        succ = x = x->rChild;
    else if (!HasRChild(*x))
    succ = x = x->lChild;
    else{
        w = w->succ();
        swap(x->data, w->data);
        BinNodePosi(T) u = w->parent;
        ((u == x) ? u->rChild: u->lChild) = succ = w->rChild;
    }
    hot = w->parent;
    if (succ) succ->parent = hot;
    release(w->data); release(w);
    return succ;
}

template<typename T>
bool BST<T>::remove(const T &e) {
    BinNodePosi(T) &x = search(e); if (!x) return false;
    removeAt(x, _hot); _size--;
    updateHeightAbove(_hot);
    return true;
}


#endif //PRACTICE_SEARCHTREE_H
