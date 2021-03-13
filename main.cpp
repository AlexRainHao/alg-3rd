#include <iostream>
#include <iterator>
#include "Vector.h"
#include "List.h"
#include "binNode.h"

using namespace std;

template <class T>
void elePrinter(T &V){
    copy(V.begin(), V.end(), ostream_iterator<int>(cout, ", "));
    cout << endl;
}

template <class T>
void elePrinter(T arr, int size){
    for (int i = 0; i < size; i++)
        cout << arr[i] << ", ";
    cout << endl;
}

int main(){
    int arr[7] = {5,1,3,2,7,4,8};
    Vector<int> V(0, 7, 0);

    for (int i = 0; i < 7; i++){
        V.insert(i, arr[i]);
    }

    V.sort(0, V.size());
    elePrinter(V, V.size());

    return 0;
}
