//
// Created by yyh on 2021/4/3.
//

#include "Vector.h"
#include "List.h"
#include "Graph.h"

template <typename Tv> struct Vertext{
    Tv data;
    int inDegree, outDegree;
    VStatus status;
    int dTime, fTime;
    int parent, priority;

    Vertext(Tv const& d = (Tv) 0):
            data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
            dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {};
};

template <typename Te> struct Edge{
    Te data;
    int weight;
    EStatus status;
    Edge(Te const& d, int w):
            data(d), weight(w), status(UNDETERMINED) {};
};

template <typename Tv, typename Te>
class GraphMatrix: public Graph<Tv, Te>{
private:
    Vector<Vertext<Tv>> V;
    Vector<Vector<Edge<Te>*>> E;

public:
    GraphMatrix(){ n = e = 0; };
    ~GraphMatrix(){
        for (int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                delete E[j][k];
    }

    /* 顶点操作 */
    virtual Tv& vertext(int i) { return V[i].data; }
    virtual Tv& inDegree(int i) { return V[i].inDegree; }
    virtual Tv& outDegree(int i) { return V[i].outDegree; }
    virtual Tv& nextNbr(int i, int j){
        while ((j > -1) && (!exists(i, --j)))
            return j;
    }
    virtual Tv& firstNbr(int i) { return nextNbr(i, n); }
    virtual VStatus& status(int i){ return V[i].status; }
    virtual Tv& dTime(int i) { return V[i].dTime; }
    virtual Tv& fTime(int i) { return V[i].fTime; }
    virtual Tv& parent(int i) { return V[i].parent; }
    virtual Tv& priority(int i) { return V[i].priority; }

    virtual int insert(Tv const& vertex){
        for (int i = 0; i < n; i++)
            E[i].insert(nullptr);
        n++;
    } // 增

    virtual Tv remove(int i){
        for (int j = 0; j < n; j++)
            if (exists(i, j)) { delete E[i][j]; V[j].inDegree--; }
        E.remove(i); n--;
        for (int j = 0; j < n; j++)
            if (exists(j, i)) {delete E[j][i]; V[j].outDegree--;}
        Tv vBak = vertex(i); V.remove(i);
        return vBak;
    } // 删

    /* 边操作 */
    virtual bool exists(int i, int j){
        return (i >= 0) && (n > i) && (j >= 0) && (n > j) && E[i][j] != nullptr;
    }

    virtual EStatus& status(int i, int j){
        return E[i][j]->status;
    }

    virtual Te& edge(int i, int j){
        return E[i][j]->data;
    }

    virtual int& weight(int i, int j){
        return E[i][j]->weight;
    }

    virtual void insert(Te const& edge, int i, int j, int w){
        if (exists(i, j)) return;
        E[i][j] = new Edge<Te>(edge, w);
        e++; V[i].outDegree++; V[j].inDegree++;
    }

    virtual Te remove(int i, int j){
        Te eBak = edge(i, j);
        delete E[i][j]; E[i][j] = nullptr;
        e--;
        V[i].outDegree--;
        V[j].inDegree--;
        return eBak;
    }
};
