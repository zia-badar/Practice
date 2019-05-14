#include "../datastructures/heap.h"

int main()
{
    heap<int> h;
    int size = 1024;
    int arr[size];


    for (int i = size; i > 0; i--)
        h.add(arr[i] = i);

    cout << "heap: \n" << h;

    cout << "removed elements: ";
    for (int i = 0; i < size; i++)
        cout << h.remove() << ((i==size-1) ? "" : ", ");

    return 0;
}