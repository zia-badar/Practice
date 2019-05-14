#include "../datastructures/binary_index_tree.h"

int main()
{
    int size = 10;
    int arr[size];
    cout << "array: ";
    for(int i=0; i<size; i++)
        cout << (arr[i] = i) << (i==size-1 ? "\n\n":", ");

    bit<int, int> t;
    t.build(arr, size, combine_function1, split_function1, map_function1, 0);
    cout << "binary index tree array for range sum: \n" << t;
    cout << "sum query from index 3 to 5: \n" << t.query(3, 5, combine_function1, split_function1, 0);

    cout << "\n\n";
    bit<string, int> t2;
    t2.build(arr, size, combine_function2,  split_function2, map_function2, "");
    cout << "binary index tree array for range string: \n" << t2;
    cout << "string query from index 3 to 5: \n" << t2.query(3, 5, combine_function2, split_function2, "");

    return 0;
}
