#include "../algorithms/sorting.h"

int main()
{
    int size = 10;
    int array[size];
    for(int i=0; i<size; i++)
        array[i] = i;

    srand(time(NULL));

    unsort(array, size, swap);
    cout << "before sorting: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n" : ", ");
    selection_sort(array, size, swap, compare);
    cout << "after selection sort: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n\n" : ", ");

    unsort(array, size, swap);
    cout << "before sorting: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n" : ", ");
    insertion_sort(array, size, compare);
    cout << "after insertion sort: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n\n" : ", ");

    unsort(array, size, swap);
    cout << "before sorting: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n" : ", ");
    merge_sort(array, 0, size-1);
    cout << "after merge sort: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n\n" : ", ");

    unsort(array, size, swap);
    cout << "before sorting: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n" : ", ");
    quick_sort(array, 0, size-1, swap);
    cout << "after quick sort: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n\n" : ", ");

    unsort(array, size, swap);
    cout << "before sorting: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n" : ", ");
    radix_sort(array, size);
    cout << "after radix sort: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n\n" : ", ");

    return 0;
}