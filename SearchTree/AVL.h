//
// Created by yyh on 2021/4/4.
//

#ifndef PRACTICE_AVL_H
#define PRACTICE_AVL_H

#include "SearchTree.h"

#define Balanced(x) (stature((x).lChild) == stature((x).rChild)
#define BalFac(x) (stature((x).lChild) - stature((x).rChild))
#define AvlBalanced(x) ((BalFac(x) > -2 && (BalFac(x) < 2))) // 高度相差不超过 1

template <typename T>
class AVL: public BST<T>{
public:
    virtual BinNodePosi(T) insert(const T&);
    virtual bool remove(const T&);
};

#define tallerChild(x)(
    stature(x->lChild) > stature(x->rChild) ? x->lChild: (
        stature(x->rChild) > stature(x->lChild) ? x->rChild: (
            IsLChild(*x) ? x->lChild: x->rChild
        )
    )
) // 取左右孩子最高者, 若等高, 取与x同侧者

template<typename T>
BinNode<T> *AVL<T>::insert(const T &e) {
    BinNodePosi(T) &x = search(e); if (x) return x;
    x = new BinNode<T>(e, _hot); _size++;

    for (BinNodePosi(T) g = _hot; g; g = g->parent){
        if (!AvlBalanced(*g)){
            FromParentTo(*g) = retateAt(tallerChild(tallerChild(g)));
            break;
        } else
            updateHeight(g);
    }
    return x;
}

template<typename T>
bool AVL<T>::remove(const T &e) {
    BinNodePosi(T) &x = search(e); if (!x) return false;
    removeAt(x, _hot); _size--;

    for (BinNodePosi(T) g = _hot; g; g = g->parent){
        if (!AvlBalanced(*g))
            g = FromParentTo(*g) = retateAt(tallerChild(tallerChild(g)));
        updateHeight(g);
    }
    return true;
}


#endif //PRACTICE_AVL_H
