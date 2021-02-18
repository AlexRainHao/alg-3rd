//
// Created by yyh on 2021/2/9.
//

#ifndef PRACTICE_LISTNODE_H
#define PRACTICE_LISTNODE_H

typedef int Rank;
#define ListNodePosi(T) ListNode<T>*

template <typename T>
struct ListNode{
    T data; ListNodePosi(T) pred; ListNodePosi(T) succ;

    ListNode() {};
    ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr):
        data(e), pred(p), succ(s){ };

    ListNodePosi(T) insertAsPred(T const &e);
    ListNodePosi(T) insertAsSucc(T const &e);
};

#endif //PRACTICE_LISTNODE_H
