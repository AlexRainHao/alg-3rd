//
// Created by AlexRain on 2021/3/13.
//

#ifndef PRACTICE_BINNODE_H
#define PRACTICE_BINNODE_H

/**************************************
* wrapper functions
**************************************/

#include <stack>
#include <queue>

#define BinNodePosi(T) BinNode<T>*
#define stature(p) (p ? p->height: -1)
typedef enum {
    RB_RED, RB_BLACK
} RBColor;

#define IsRoot(x) (x.parent != nullptr)
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lChild))
#define IsRChild(x) (!ISroot(x) && (&(x) == (x).parent->lRChild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) (x.lChild != nullptr)
#define HasRChild(x) (x.rChild != nullptr)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))

#define brother(p)(\
    IsLChild(*p) ? \
        p->parent->rChild: \
        p->parent->lChild)

#define uncle(p)(\
    IsLChild(*((p)->parent)) ? \
        p->parent->parent->rChild: \
        p->parent->parent->lChild)

#define FromParentTo(p)(\
    IsRoot(p) ? _root: (\
    IsLChild(p) ? p.parent->lChild: p.parent->rChild\
    )\
)



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

//    int size();
    BinNodePosi(T) insertAsLC(T const&); // insert as left child
    BinNodePosi(T) insertAsRC(T const&); // insert as right child
    BinNodePosi(T) succ();

    template<typename VST> void travLevel(VST&); // 层次遍历 where VST as a param for return's type of given function
    template<typename VST> void travPre(VST&);// 前序遍历
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

template<typename T>
BinNodePosi(T) BinNode<T>::succ() {
    BinNodePosi(T) s = this;

    if (rChild){
        s = rChild;
        while (HasLChild(*s)) s = s->lChild;
    } else {
        while (IsRChild(*s)) s = s->parent;
        s = s->parent;
    }
    return s;
}

// 各遍历的递归
template <typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit){
    if (!x) return;
    visit(x->data);
    travPre_R(x->lChild, visit);
    travPre_R(x->rChild, visit);
}

template <typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST& visit){
    if (!x) return;
    travPost_R(x->lChild, visit);
    travPost_R(x->rChild, visit);
    visit(x->data);
}

template <typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST& visit){
    if (!x) return;
    travIn_R(x->lChild, visit);
    visit(x->data);
    travIn_R(x->rChild, visit);

}


// 先序遍历两种方法
template <typename T, typename VST>
void travPre_V1(BinNodePosi(T) x, VST& visit){
    std::stack<BinNodePosi(T)> S;
    if (x != nullptr) S.push(x);

    while (!S.empty()){
        x = S.top(); S.pop();
        visit(x->data);
        if HasRChild(*x) S.push(x->rChild);
        if HasLChild(*x) S.push(x->lChild);
    }
}

template <typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, std::stack<BinNodePosi(T)>& S){
    while (x){
        visit(x->data);
        S.push(x->rChild);
        x = x->lChild;
    }
}

template <typename T, typename VST>
void travPre_V2(BinNodePosi(T) x, VST& visit){
    std::stack<BinNodePosi(T)> S;
    while (true){
        visitAlongLeftBranch(x, visit, S);
        if (S.empty()) break;
        x = S.top(); S.pop();
    }
}


// 中序遍历
template <typename T, typename VST>
static void goAlongLeftBranch(BinNodePosi(T) x, std::stack<BinNodePosi(T)> &S){
    while(x){
        S.push(x);
        x = x->lChild;
    }
}

template <typename T, typename VST>
void tranIn_V1(BinNodePosi(T) x, VST& visit){
    std::stack<BinNodePosi(T)> S;
    while (true){
        goAlongLeftBranch(x, S);
        if (S.empty()) break;

        x = S.top(); S.pop(); visit(x->data);
        x = x->rChild;
    }
}

template <typename T, typename VST>
void tranIn_V2(BinNodePosi(T) x, VST& visit){
    std::stack<BinNodePosi(T)> S;
    while(true){
        if (x){
            S.push(x);
            x = x->lChild;
        } else if (!S.empty()) {
            x = S.top(); S.pop();
            visit(x->data);
            x = x->rChild;
        } else
            break;
    }
}

template <typename T, typename VST>
void tranIn_V3(BinNodePosi(T) x, VST& visit){
    bool backtrack = false;

    while (true){
        if (!backtrack && HasLChild(*x))
            x = x->lChild;
        else{
            visit(x->data);
            if (HasRChild(*x)){
                x = x->rChild;
                backtrack = false;
            } else {
                if (!(x = x->succ())) break;
                backtrack = true;
            }
        }
    }
}

// 后序遍历
template <typename T, typename VST>
void gotoHLVFL(std::stack<BinNodePosi(T)> &S){
    while (BinNodePosi(T) x = S.top()){
        if (HasLChild(*x)) {
            if (HasRChild(*x)) S.push(x->rChild);
            S.push(x->lChild);
        } else
            S.push(x->rChild);
    }
    S.pop();
}

template <typename T, typename VST>
void tranPost_V1(BinNodePosi(T) x, VST& visit){
    std::stack<BinNodePosi(T)> S;
    if (x) S.push(x);
    while(!S.empty()){
        if (S.top() != x->parent) // has brother
            gotoHLVFL(S);
        x = S.top(); S.pop();
        visit(x->data);
    }
}

template<typename T>
template<typename VST>
void BinNode<T>::travPre(VST &visit) {
    travPost_R(this, visit);
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn(VST &visit) {
    travIn_R(this, visit);
}

template<typename T>
template<typename VST>
void BinNode<T>::travPost(VST &visit) {
    travPost_R(this, visit);
}

template<typename T>
template<typename VST>
void BinNode<T>::travLevel(VST &) {
    std::queue<BinNodePosi(T)> Q;

    Q.push(this);
    while(!Q.empty()) {
        BinNodePosi(T) x = Q.front();
        Q.pop();

        visit(x->data);
        if (HasLChild(*x)) Q.push(x->lChild);
        if (HasRChild(*x)) Q.push(x->rChild);
    }
}


#endif //PRACTICE_BINNODE_H
