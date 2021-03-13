//
// Created by AlexRain on 2021/3/13.
//

#ifndef PRACTICE_BINNODE_H
#define PRACTICE_BINNODE_H

/**************************************
* wrapper functions
**************************************/

#define BinNodePosi(T) BinNode<T>*
#define stature(p) (p ? p->height: -1)
typedef enum {
    RB_RED, RB_BLACK
} RBColor;

#define IsRoot(x) (x->parent != nullptr)
#define IsLChild(x) (!IsRoot(x) && (&(x) == x.parent->lChild))
#define IsRChild(x) (!ISroot(x) && (&(x) == x.parent->lRChild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) (x->lChild != nullptr)
#define HasRChild(x) (x->rChild != nullptr)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))

#define brother(p)(IsLChild(p) ? p->parent->rChild: p->parent->lChild)
#define uncle(p)(IsLChild(p->parent) ? p->parent->parent->rChild: p->parent->parent->lChild)
#define FromParentTo(p)(IsRoot(p) ? _root: (IsLChild(p) ? p.parent->lChild: p.parent->rChild))


template<typename T>
struct BinNode {
    T data;
    BinNodePosi(T)parent;
    BinNodePosi(T)lChild;
    BinNodePosi(T)rChild;

    int height;
    int npl;
    RBColor color;

    // constructor
    BinNode() : parent(nullptr), lChild(nullptr), rChild(nullptr),
                height(0), npl(1), color(RB_RED) {};

    BinNode(T e, BinNodePosi(T)p = nullptr, BinNodePosi(T)lc = nullptr, BinNodePosi(T)rc = nullptr,
            int h = 0, int l = 1, RBColor c = RB_RED) :
            data(e), parent(p), lChild(lc), rChild(rc), height(h), npl(l), color(c) {};

    int size();
    BinNodePosi(T) insertAsLC(T const&); // insert as left child
    BinNodePosi(T) insertAsRC(T const&); // insert as right child
    BinNodePosi(T) succ();

    template<typename VST> void travLevel(VST&); // 层次遍历 where VST as a param for return's type of given function
    template<typename VST> void travPre(VST&); // 前序遍历
    template<typename VST> void travIn(VST&); // 中序遍历
    template<typename VST> void travPost(VST&); // 后序遍历

    bool operator<(BinNode const& bn){ return data < bn.data; };
    bool operator>(BinNode const& bn){ return data > bn.data; };
    bool operator==(BinNode const &bn) { return data == bn.data; }


};


template<typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(const T &e) {
    return lChild = new BinNode(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(const T &e) {
    return rChild = new BinNode(e, this);
}

#endif //PRACTICE_BINNODE_H
