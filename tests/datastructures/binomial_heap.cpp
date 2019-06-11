#include<iostream>

#include "../../datastructures/binomial_heap.h"
#include "../../algorithms/sorting.h"

using namespace std;

int main()
{
    binomial_heap<int> bh;
    int size = 1024;
    int unsorted[size];
    for(int i=0; i<size; i++) unsorted[i] = i;

    unsort(unsorted, size, swap);

    cout << "pushing: ";
    for(int i=0; i<size; i++)
        bh.push(unsorted[i]), cout << unsorted[i] << (i==size-1 ? "\n" : ", ");

    cout << "popped: ";
    for(int i=0; i<size; i++)
        cout << *bh.pop() << (i==size-1 ? "\n" : ", ");

    return 0;
}