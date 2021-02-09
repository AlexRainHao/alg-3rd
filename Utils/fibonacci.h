//
// Created by yyh on 2021/2/9.
//

#ifndef PRACTICE_FIBONACCI_H
#define PRACTICE_FIBONACCI_H

class Fib{
private:
    int f, g;
public:
    Fib(int n);
    int get();
    int next();
    int prev();
};

Fib::Fib(int n){
    f = 0, g = 1;
    while (g < n) next();
}

int Fib::get(){ return g; }

int Fib::next() {
    g += f;
    f = g - f;
    return g;
}

int Fib::prev(){
    f = g - f;
    g -= f;
    return g;
}

#endif //PRACTICE_FIBONACCI_H
