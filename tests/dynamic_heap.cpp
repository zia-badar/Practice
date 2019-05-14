#include "../datastructures/dynamic_heap.h"

int main()
{
    dynamic_heap<int> heap;
    int size = 1024;
    int arr[size];


    for (int i = size; i > 0; i--)
        heap.add(arr[i] = i);


    cout << "removed elements: ";
    for (int i = 0; i < size; i++)
        cout << heap.remove() << ((i==size-1) ? "" : ", ");


    return 0;
}