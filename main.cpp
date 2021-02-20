#include <iostream>
#include <iterator>

//#include "Vector.h"
//#include "List.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

template <class T>
void elePrinter(T &V){
    copy(V.begin(), V.end(), ostream_iterator<int>(cout, ", "));
    cout << endl;
}

template <class T>
void elePrinter(T arr, int size){
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", " << std::flush;
    }
}


int main() {
    int arr[7] = {5, 1, 3, 2, 7, 4, 8};
//    Stack<int> s(arr, 7);
    Queue<int> q(arr, 7);
    cout << q.dequeue() << endl;
    cout << q.front() << endl;

}
