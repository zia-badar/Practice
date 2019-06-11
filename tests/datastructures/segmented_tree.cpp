#include "../../datastructures/segmented_tree.h"

int main()
{
    int size = 10;
    int arr[size];
    for(int i=0; i<size; i++)
        arr[i] = i;

    segmented_tree<int, int> tree;
    tree.build(arr, size, combine_function1, map_function1);
    cout << "sum from 1 to 9: " << tree.query(1, 9,  combine_function1, 0) << endl;
    cout << "sum from 3 to 8: " << tree.query(3, 8,  combine_function1, 0) << endl;
    cout << "sum from 7 to 7: " << tree.query(7, 7,  combine_function1, 0) << endl;

    segmented_tree<string, int> *t2 = new segmented_tree<string, int>();
    t2->build(arr, size, combine_function2, map_function2);
    cout << "range string from 3 to 8 is: " << t2->query(3, 8, combine_function2, "") << endl;
    delete t2;


    return 0;
}