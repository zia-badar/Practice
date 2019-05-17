#include "../datastructures/dynamic_heap.h"

int main()
{
    dynamic_heap<int> heap;
    int size = 32;
    int arr[size];

    cout << "adding: ";
    for (int i = size-1; i >= 0; i--)
    {
        cout << i << (i == 0 ? "\n" : ", ");
        heap.add(arr[i]=i);
    }
    cout << "heap: " << heap;

    cout << "removing: ";
    for (int i = 0; i < size; i++)
        cout << heap.remove() << (i == size-1 ? "\n" : ", ");
    cout << "heap: \n" << heap;

    cout << "adding: ";
    for (int i = size-1; i >= 0; i--)
    {
        cout << i << (i == 0 ? "\n" : ", ");
        heap.add(arr[i]=i);
    }
    cout << "heap: " << heap;

    cout << "decreasing each value by 2 times of its value\n";
    for (int i = 0; i < size; i++)
        heap.decrease_entry(arr[i], 2*arr[i]);
    cout << "heap: " << heap;

    cout << "removing: ";
    for (int i = 0; i < size; i++)
        cout << heap.remove() << (i == size-1 ? "\n" : ", ");
    cout << "heap: \n" << heap;

    return 0;
}