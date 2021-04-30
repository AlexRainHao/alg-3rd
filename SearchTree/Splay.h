//
// Created by yyh on 2021/4/6.
//

#ifndef PRACTICE_SPLAY_H
#define PRACTICE_SPLAY_H

#include "SearchTree.h"

template<typename T>
class Splay: public BST<t>{
protected:
    BinNodePosi(T) splay(BinNodePosi(T) v); // 节点v伸展至根
public:
    BinNodePosi(T) & search(const T&);
    BinNodePosi(T) insert(const T&);
    bool remove(const T&);
};

template <typename NodePosi>
inline void attachAsLChild(NodePosi p, NodePosi lc){
    p->lChild = lc;
    if (lc)
        lc->parent = p;
}

template <typename NodePosi>
inline void attachAsRChild(NodePosi p, NodePosi rc){
    p->rChild = rc;
    if (rc)
        rc->parent = p;
}

template <typename T>
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v) {
    if (!v) return nullptr;
    BinNodePosi(T) p; BinNodePosi(T) g;

    while((p = v->parent) && (g = p->parent)){
        BinNodePosi(T) gg = g->parent;

        if (IsLChild(*v))
            if (IsLChild(*p)){
                attachAsLChild(g, p->rChild); attachAsLChild(p, v->rChild);
                attachAsRChild(p, g); attachAsRChild(v, p);
            } else {
                attachAsLChild(p, v->rChild); attachAsRChild(g, v->lChild);
                attachAsLChild(v, g); attachAsRChild(v, p);
            }
        else if (IsRChild(*p)){
            attachAsRChild(g, p->lChild); attachAsRChild(p, v->lChild);
            attachAsLChild(p, g); attachAsLChild(v, p);
        } else {
            attachAsRChild(p, v->lChild); attachAsLChild(g, v->rChild);
            attachAsRChild(v, g); attachAsLChild(v, p);
        }

        if (!gg) v->parent = nullptr;
        else
            (g == gg->lChild) ? attachAsLChild(gg, v) : attachAsLChild(gg, v);
        updateHeight(g); updateHeight(p); updateHeight(v);
    } // g mush nullptr, but p may be nullptr

    if (p = v->parent){
        if (IsLChild(*v)) { attachAsLChild(p, v->rChild); attachAsRChild(v, p); }
        else { attachAsRChild(p, v->lChild); attachAsLChild(v, p); }
        updateHeight(p); updateHeight(v);
    }
    v->parent = nullptr;
    return v;
}

template<typename T>
BinNodePosi(T) &Splay<T>::search(const T &e) {
    BinNodePosi(T) p = searchIn(_root, e, _hot = nullptr);
    _root = splay((p? p: _hot));
    return _root;
}

template<typename T>
BinNodePosi(T) Splay<T>::insert(const T &e) {
    if (!_root) { _size++; return _root = new BinNodePosi(T) (e); }
    if (e == search(e)->data) return _root;

    _size++; BinNodePosi(T) t = _root;
    if (_root->data < e){
        t->parent = _root = new BinNode<T>(e, nullptr, t, t->rChild);
        if (HasRChild(*t)) { t->rChild->parent = _root; t->rChild = nullptr; }
    } else {
        t->parent = _root = new BinNode<T>(e, nullptr, t->lChild, t);
        if (HasLChild(*t)) { t->lChild->parent = _root; t->lChild = nullptr;}
    }
    updateHeightAbove(t);
    return _root;
}

template<typename T>
bool Splay<T>::remove(const T &e) {
    if (!_root || (e != search(e)->data)) return false;
    BinNodePosi(T) w = _root;

    if (!HasLChild(*_root)) {
        _root = _root->rChild;
        if (_root) _root->parent = nullptr;
    } else if (!HasRChild(*_root)) {
        _root = _root->lChild;
        if (_root) _root->parent = nullptr;
    } else {
        BinNodePosi(T) lTree = _root->lChild;
        lTree->parent = nullptr;
        _root->lChild = nullptr; _root = _root->lChild; _root->parent = nullptr;
        search(w->data);
        _root->lChild = lTree; lTree->parent = _root;
    }
    release(w->data); release(w); _size--;
    if (_root) updateHeight(_root);
    return true;
}



#endif //PRACTICE_SPLAY_H
