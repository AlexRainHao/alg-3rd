//
// Created by AlexRain on 2021/2/14.
//

#ifndef PRACTICE_NUMERAL_CONVERTER_H
#define PRACTICE_NUMERAL_CONVERTER_H

#include "Stack.h"

namespace bitConvert {
    static char digit[] = {
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
            'A', 'B', 'C', 'D', 'E', 'F'
    };


    void converter(Stack<char> &S, int n, int base) {
        if (n > 0) {
            converter(S, n / base, base);
            S.push(digit[n % base]);
        }
    }

    void converter_loop(Stack<char> &S, int n, int base) {
        while (n > 0) {
            int remainder = (int) (n % base);
            S.push(digit[remainder]);
            n /= base;
        }
    }
}

namespace bracketsBalance{
    void trim(const char exp[], int &lo, int &hi){
        while ((lo <= hi) && (exp[lo] != '(') && (exp[lo] != ')')) lo++;
        while ((lo <= hi) && (exp[hi] != '(') && (exp[hi] != ')')) hi--;
    }

    int divide(const char exp[], int lo, int hi) {
        int mi = lo;
        int crc = 1;

        while ((crc > 0) && (++mi < hi)) {
            if (exp[mi] == ')') crc--;
            if (exp[mi] == '(') crc++;
        }
        return mi;
    }

    bool paren(const char exp[], int lo, int hi){
        trim(exp, lo, hi);
        if (lo > hi) return true;
        if (exp[lo] == ')') return false;
        if (exp[hi] == '(') return false;

        int mi = divide(exp, lo, hi);
        if (mi > hi) return false;

        return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi);
    }

    bool paren_loop(const char exp[], int lo, int hi){
        Stack<char> S;
        for (int i = 0; exp[i]; i++){
            switch(exp[i]){
                case '(': S.push(exp[i]); break;
                case ')': if ((S.empty()) || (S.pop() != '(')) return false; break;
                default: break;
            }
        }
        return S.empty();
    }
}

namespace labyrinthPath {
    #define LABY_MAX 24
    typedef enum {
        AVAILABLE, ROUTE, BACKTRACKED, WALL
    } Status;
    typedef enum {
        UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY
    } ESWN;

    inline ESWN nextESWN(ESWN eswn) {
        return ESWN(eswn + 1);
    }

    struct Cell {
        int x, y;
        Status status;
        ESWN incoming, outgoing;
    };

    Cell laby[LABY_MAX][LABY_MAX];

    inline Cell *neighbor(Cell *cell) {
        switch (cell->outgoing) {
            case EAST:
                return cell + 1;
            case SOUTH:
                return cell + LABY_MAX;
            case WEST:
                return cell - 1;
            case NORTH:
                return cell - LABY_MAX;
            default:
                exit(-1);
        }
    }

    inline Cell *advance(Cell *cell) {
        Cell *next;
        switch (cell->outgoing) {
            case EAST:
                next = cell + 1;
                next->incoming = WEST;
                break;
            case SOUTH:
                next = cell + LABY_MAX;
                next->incoming = NORTH;
                break;
            case WEST:
                next = cell - 1;
                next->incoming = EAST;
                break;
            case NORTH:
                next = cell - LABY_MAX;
                next->incoming = SOUTH;
                break;
            default:
                exit(-1);
        }
        return next;
    }

    bool labyrinth(Cell laby[LABY_MAX][LABY_MAX], Cell *s, Cell *t) {
        if ((AVAILABLE != s->status) || (AVAILABLE != t->status)) return false;
        Stack<Cell *> path;
        s->incoming = UNKNOWN;
        s->status = ROUTE;
        path.push(s);

        do {
            Cell *c = path.top();
            if (c == t) return true;
            while (NO_WAY > (c->outgoing = nextESWN(c->outgoing)))
                if (AVAILABLE == neighbor(c)->status)
                    break;
            if (NO_WAY <= c->outgoing) {
                c->status = BACKTRACKED;
                c = path.pop();
            }
            else {
                path.push(c = advance(c));
                c->outgoing = UNKNOWN;
                c->status = ROUTE;
            }
        } while (!path.empty());
        return false;
    }
}

#endif //PRACTICE_NUMERAL_CONVERTER_H
