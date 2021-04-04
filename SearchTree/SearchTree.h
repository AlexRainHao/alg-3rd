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

template<typename T>
BinNodePosi(T) BST<T>::connect34(BinNode<T> *a, BinNode<T> *b, BinNode<T> *c,
        BinNode<T> *T0, BinNode<T> *T1, BinNode<T> *T2, BinNode<T> *T3) {

    a->lChild = T0; if (T0) T0->parent = a;
    a->rChild = T1; if (T1) T1->parent = a;
    updateHeight(a);

    c->lChild = T2; if (T2) T2->parent = c;
    c->rChild = T3; if (T3) T3->parent = c;
    updateHeight(c);

    b->lChild = a; a->parent = b;
    b->rChild = c; c->parent = b;
    updateHeight(b);

    return b;
}

template<typename T>
BinNodePosi(T) BST<T>::retateAt(BinNodePosi(T) v) {
    BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent;

    if (IsLChild(*p))
        if (IsLChild(*v)){
            p->parent = g->parent;
            return connect34(v, p, g, v->lChild, v->rChild, p->rChild, g->rChild);
        } else {
            v->parent = g->parent;
            return connect34(p, v, g, p->lChild, v->rChild, v->rChild, g->rChild);
        }

    else
        if (IsRChild(*v)) {
            p->parent = g->parent;
            return connect34(g, p, v, g->lChild, p->lChild, v->lChild, v->rChild);
        } else {
            return connect34(g, v, p, g->lChild, v->lChild, v->rChild, p-rChild);
        }
}


#endif //PRACTICE_SEARCHTREE_H
