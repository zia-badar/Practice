#include "../datastructures/avl.h"

int main()
{
    avl<int> t;
    int size = 1023;        // 2^n-1 elements creates n height avl tree
    int arr[size];


    for (int i = 0; i < size; i++)
        t.add(arr[i] = i+1);

    cout << t;

    return 0;
}