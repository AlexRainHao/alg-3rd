//
// Created by yyh on 2021/4/6.
//

#ifndef PRACTICE_BTREE_H
#define PRACTICE_BTREE_H

#include "Vector.h"

#define BTNodePosi(T) BTNode<T>*


template <typename T>
struct BTNode {
    BTNodePosi(T)parent;
    Vector<T> key;
    Vector<BTNodePosi(T)> child;

    BTNode() {
        parent = nullptr;
        child.insert(0, nullptr);
    }
    BTNode(T e, BTNodePosi(T) lc = nullptr, BTNodePosi(T) rc = nullptr){
        parent = nullptr;
        key.insert(0, e);
        child.insert(0, lc); child.insert(1, rc);
        if (lc) lc->parent = this;
        if (rc) rc->parent = this;
    }
};


template <typename T>
class BTree{
protected:
    int _size;
    int _order;
    BTNodePosi(T) _root;
    BTNodePosi(T) _hot;
    void solveOverflow(BTNodePosi(T)); // 插入上溢，分裂
    void solveUnderflow(BTNodePosi(T)); // 删除下溢，合并

public:
    BTree(int order = 3): _order(order), _size(0){
        _root = new BTNode<T>();
    }
    ~BTree() { if (_root) release(_root); }
    int const order() { return _order; }
    int const size() { return _size; }
    BTNodePosi(T) & root() { return _root; }
    bool empty() const { return !_root; }
    BTNodePosi(T) search(const T&);
    bool insert(const T&);
    bool remove(const T&);
};

template<typename T>
BTNodePosi(T) BTree<T>::search(const T &e) {
    BTNodePosi(T) v = _root; _hot = nullptr;
    while (v){
        Rank r = v->key.search(e);
        if ((0 <= r) && (e == v->key[r])) return v;
        _hot = v;
        v = v->child[r + 1];
    }
    return nullptr;
}

template<typename T>
bool BTree<T>::insert(const T &) {
    BTNodePosi(T) v = search(e); if (v) return false;
    Rank r = _hot->key.search(e);
    _hot->key.insert(r + 1, e);
    _hot->child.insert(r + 2, nullptr);
    _size++;
    solveOverflow(_hot);
    return true;
}


#endif //PRACTICE_BTREE_H
