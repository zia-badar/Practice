#include "../datastructures/dynamic_heap.h"

int main()
{
    dynamic_heap<int> heap;
    int size = 5;
    int arr[size];


    for (int i = size; i > 0; i--)
    {
        cout << "------------------------------------------------\n";
        cout << "before:\n" << heap << endl;
        cout << "added: " << i << "\n\n";
        heap.add(arr[i]=i);
        cout << "after:\n" << heap << endl;
        cout << "------------------------------------------------\n";
    }

    for (int i = 0; i < size; i++)
    {
        cout << "------------------------------------------------\n";
        cout << "before:\n" << heap << endl;
        cout << "removed: " << heap.remove() << "\n\n";
        cout << "after:\n" << heap << endl;
        cout << "------------------------------------------------\n";
    }


    return 0;
}