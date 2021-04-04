//
// Created by yyh on 2021/4/3.
//

#ifndef PRACTICE_GRAPH_H
#define PRACTICE_GRAPH_H

#include <stack>
#include <iostream>
#include "Queue.h"

typedef enum { UNDISCOVERED, DISCOVERED, VISITED} VStatus;
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EStatus;

template <typename Tv, typename Te>
class Graph{
private:
    void reset(){
        // 重置顶点
        for (int i = 0; i < n; i++){
            status(i) = UNDISCOVERED; dTime(i) = fTime(i) = -1;
            parent(i) = -1; priority(i) = INT_MAX;

            // 重置边
            for (int j = 0; j < n; j++)
                if (exists(i, j))
                    status(i, j) = UNDETERMINED;
        }
    }

public:
    /* 顶点信息 */
    int n; //顶点总数
    virtual int insert(Tv const&) = 0; //插入顶点
    virtual Tv remote(int) = 0; //删除顶点及其关联边
    virtual Tv& vertext(int) = 0; //顶点v的数据
    virtual int inDegree(int) = 0;
    virtual int outDegree(int) = 0;
    virtual int firstNbr(int) = 0; //顶点v的首个邻接顶点
    virtual int nextNbr(int, int) = 0; //顶点v相对于顶点j的下一邻接顶点;
    virtual VStatus& status(int) = 0;
    virtual int& dTime(int) = 0;
    virtual int& fTime(int) = 0;
    virtual int& parent(int) = 0; //顶点v在遍历树中的父亲
    virtual int& priority(int) = 0; //顶点v在遍历树的优先级数

    /* 边信息 */
    int e; //边数
    virtual bool exists(int, int) = 0; //边是否存在
    virtual void insert(Te const&, int, int, int) = 0; //顶点v,u之间插入权重w的边
    virtual Te remove(int, int) = 0; //删除顶点间的边
    virtual EStatus& status(int, int) = 0; //边的状态
    virtual Te& edge(int, int) = 0; //边的数据
    virtual int& weight(int, int) = 0; //边的权重

    /* 算法 */
    void bfs(int); //广度优先搜索
    void BFS(int, int&);
    void dfs(int); //深度优先搜索
    void DFS(int, int&);
    std::stack<Tv>*tSort(int); //DFS的拓扑排序
    bool TSort(int, std::stack<Tv>* S);
    void bcc(int); //DFS的双连通分量分解
    void BCC(int, int&, std::stack<int>&);
    template <typename PU> void pfs(int, PU); //优先级搜索框架
    template <typename PU> void PFS(int, PU);
};

template<typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s) {
    reset(); int clock = 0; int v = s;
    do
        if (UNDISCOVERED == status(v))
            BFS(v, clock);
    while (s != (v = (++v % n))); // 有点骚...
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int &clock) {
    Queue<int> Q;
    status(v) = DISCOVERED; Q.enqueue(v);
    while (!Q.empty()){
        int v = Q.dequeue(); dTime(v) = ++clock;

        for (int u = firstNbr(v); u > -1; u = nextNbr(v, u))
            if (UNDISCOVERED == status(u)){
                status(u) = UNDISCOVERED; Q.enqueue(u);
                status(u, v) = TREE; parent(u) = v;
            } else{
                status(v, u) = CROSS;
            }

        status(v) = VISITED;
    }
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s) {
    reset(); int clock = 0; int v = s;
    do
        if (UNDISCOVERED == status(v))
            DFS(v, clock);
    while( s != (v = (++v % n)));
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int &clock) {
    dTime(v) = ++clock; status(v) = DISCOVERED;

    for (int u = firstNbr(v); u > -1; u = nextNbr(v, u))
        switch (status(u)){
        case UNDISCOVERED:
            status(v, u) = TREE; parent(u) = v; DFS(u, clock); break;
        case DISCOVERED:
            status(v, u) = BACKWARD; break;
        default:
            status(v, u) = (dTime(v) < dTime(u)) ? FORWARD: CROSS; break;
    }

    status(v) = VISITED; fTime(v) = ++clock;
}

template<typename Tv, typename Te>
bool Graph<Tv, Te>::TSort(int v, std::stack<Tv> *S) {
    status(v) = DISCOVERED;
    for (int u = firstNbr(v); u > -1; u = nextNbr(v, u))
        switch(status(u)){
            case UNDISCOVERED:
                parent(u) = v;
                if (!TSort(u, S)) return false;
                break;
            default:
                break;
    }
    status(v) = VISITED; S->push(vertex(v));
    return true;
}

template<typename Tv, typename Te>
std::stack<Tv> *Graph<Tv, Te>::tSort(int s) {
    reset(); int clock = 0; int v = s;
    std::stack<Tv>* S = new std::stack<Tv>;

    do {
        if (UNDISCOVERED == status(v))
            if (!TSort(v, clock, S)){
                while (!S->empty())
                    S->pop(); break;
            }
    } while (s != (v = (++v % n)));
    return S;
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int s) {
    reset(); int clock = 0; int v = s; std::stack<int> S;
    do
        if (UNDISCOVERED == status(v)){
            BCC(v, clock, S);
            S.pop();
        }
    while( s != (v = (++v % n)));
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int v, int &clock, std::stack<int> &S) {
    fTime(v) = dTime(v) = ++clock; status(v) = DISCOVERED; S.push(v);
    for (int u = firstNbr(v); u > -1; u = nextNbr(v, u))
        switch(status(u)){
        case UNDISCOVERED:
            parent(u) = v; status(v, u) = TREE; BCC(u, clock, S);
            if (fTime(u) < dTime(v))
                fTime(v) = min(fTime(v), fTime(u));
            else{
                while(v != S.top()) S.pop();
                S.push(v);
            }
            break;
        case DISCOVERED:
            status(v, u) = BACKWARD;
            if (u != parent(v)) fTime(v) = min(fTime(v), dTime(u));
            break;
        default:
            status(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
            break;
    }
    status(v) = VISITED;
}

template<typename Tv, typename Te>
template<typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater) {
    reset(); int v = s;
    do
        if (UNDISCOVERED == status(v))
            PFS(v, prioUpdater);
    while(s != (v = (++v % n)));
}

template<typename Tv, typename Te>
template<typename PU>
void Graph<Tv, Te>::PFS(int s, PU prioUpdater) {
    priority(s) = 0; status(s) = VISITED; parent(s) = -1;
    while(true){
        for (int w = firstNbr(s); w > -1; w = nextNbr(s, w))
            prioUpdater(this, s, w);
        for (int shortest = INT_MAX, w = 0; w < n; w++)
            if (status(w) == UNDISCOVERED)
                if (shortest > priority(w)){
                    shortest = priority(w); s = w;
                }
        if (status(s) == VISITED) break;
        status(s) = VISITED; status(parent(s), s) = TREE;
    }
}


template<typename Tv, typename Te> struct BfsPU{
    virtual void operator()(Graph<Tv, Te>* g, int u, int v){
        if (g->status(v) == UNDISCOVERED)
            if (g->priority(v) > g->priority(u) + 1){
                g->priority(v) = g->priority(u) + 1;
                g->parent(v) = u;
            }
    }
};

template <typename Tv, typename Te> struct DfsPU{
    virtual void operator()(Graph<Tv, Te>* g, int u, int v){
        if (g->status(v) == UNDISCOVERED)
            if (g->priority(v) > g->priority(u) - 1){
                g->priority(v) = g->priority(u) - 1;
                g->parent(v) = u;
                return;
            }
    }
};


#endif //PRACTICE_GRAPH_H
