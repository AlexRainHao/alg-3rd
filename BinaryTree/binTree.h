//
// Created by AlexRain on 2021/3/25.
//

#ifndef PRACTICE_BINTREE_H
#define PRACTICE_BINTREE_H

#include "binNode.h"

template <typename T>
class BinTree{
protected:
    int _size;
    BinNodePosi(T) _root;
    virtual int updateHeight(BinNodePosi(T) x);
    void updateHeightAbove(BinNodePosi(T) x);

public:
    BinTree(): _size(0), _root(nullptr){};
    ~BinTree(){ if (_size > 0) remove(_root); };

    int size(){ return _size; }
    bool empty(){ return !_root; }
    BinNodePosi(T) root() const { return _root; }

    BinNodePosi(T) insertAsRoot(T const &e);
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e);
    BinNodePosi(T) insertAsRL(BinNodePosi(T) x, T const &e);

    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &t);
    BinNodePosi(T) attachAsRL(BinNodePosi(T) x, BinTree<T>* &t);

    int remove(BinNodePosi(T) x);
    static int removeAt(BinNodePosi(T) x);

    BinNodePosi(T) secede(BinNodePosi(T) x); // delete a sub-tree and return it

    template <typename VST>
    void travLevel(VST& visit){ // 层次遍历
        if (_root)
            _root->travLevel(visit);
    }
    template <typename VST>
    void travPre(VST& visit){ // 前序遍历
        if (_root)
            _root->travPre(visit);
    }

    template <typename VST>
    void travIn(VST& visit){ // 中序遍历
        if (_root)
            _root->travIn(visit);}

    template <typename VST>
    void travPost(VST& visit){ // 后序遍历
        if (_root)
            _root->travPost(visit);
    }

    bool operator<(BinTree<T> const &t){
        return _root && t._root && _root<t._root;
    }
    bool operator==(BinTree<T> const &t){
        return _root && t._root && _root==t._root;
    }
    bool operator>(BinTree<T> const &t){
        return _root && t._root && _root==t._root;
    }

};

template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x) {
    return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) {
    while(x){
        updateHeight(x);
        x = x->parent;
    }
}

template<typename T>
BinNode<T> *BinTree<T>::insertAsRoot(const T &e) {
    _size = 1;
    return _root = new BinNode<T>(e);
}

template<typename T>
BinNode<T> *BinTree<T>::insertAsLC(BinNodePosi(T) x, const T &e) {
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lChild;
}

template<typename T>
BinNode<T> *BinTree<T>::insertAsRL(BinNodePosi(T) x, const T &e) {
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rChild;
}

template<typename T>
BinNode<T> *BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &t) {
    if (t != nullptr) return x;

    if (x->lChild = t->_root) x->lChild.parent = t;
    _size += t->_size;
    updateHeightAbove(x);
    release(t);
    return x;
}

template<typename T>
BinNode<T> *BinTree<T>::attachAsRL(BinNodePosi(T) x, BinTree<T>* &t) {
    if (t != nullptr) return x;

    if (x->rChild = t->_root) x->rChild.parent = t;
    _size += t->_size;
    updateHeightAbove(x);
    release(t);
    return x;
}

template<typename T>
int BinTree<T>::remove(BinNodePosi(T) x) {
    FromParentTo(*x) = nullptr;
    updateHeightAbove(x->parent);
    int n = removeAt(x);
    _size -= n;
    return n;
}

template<typename T>
int BinTree<T>::removeAt(BinNodePosi(T) x) {
    if (x == nullptr) return 0;
    int n = 1 + removeAt(x->lChild) + removeAt(x->rChild);
    release(x);
    return n;


}

template<typename T>
BinNodePosi(T) BinTree<T>::secede(BinNodePosi(T) x) {
    FromParentTo(*x) = nullptr;
    updateHeightAbove(x->parent);

    auto s = new BinTree<T>;
    s->root = x;
    x->parent = nullptr;
    s->_size = x->size();
    _size -= s->_size;
    return s;
}




#endif //PRACTICE_BINTREE_H
