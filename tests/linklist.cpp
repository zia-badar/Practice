#include "../datastructures/linklist.h"

int main()
{
    linklist<int> l, l2;
    int size = 10;
    int arr[size];
    int arr2[size];

    //-------------------------------------------------------------------------------
    cout << "add opeartion\n";
    for(int i=0; i<size; i++) l.add(arr[i]=i);
    cout << l << "\n\n\n";
    l.clear();
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    cout << "remove opeartion\n";
    for(int i=0; i<size; i++) l.add(arr[i]=i);
    for(int i=0; i<size/2; i++) l.remove(i);
    cout << l << "\n\n\n";
    l.clear();
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    cout << "ith element access opeartion\n";
    for(int i=0; i<size; i++) l.add(arr[i]=i);
    for(int i=0; i<size; i++) cout << l[i] << (i == 9 ? "\n\n\n" : ", ");
    l.clear();
    //-------------------------------------------------------------------------------


    //-------------------------------------------------------------------------------
    cout << "combining linklists opeartion\n";
    for(int i=0; i<size; i++) l.add(arr[i]=i);
    for(int i=0; i<size; i++) l2.add(arr2[i]=size+i);
    l += l2;
    cout << l << "\n\n\n";
    l.clear();
    l2.clear();
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    cout << "iterator opeartion\n";
    for(int i=0; i<10; i++) l.add(arr[i]=i);
    for(linklist<int>::iterator iter = l.begin(); iter != l.end(); iter++)
         cout << *iter << ", ";
    cout << "\n\n\n";
    l.clear();
    //-------------------------------------------------------------------------------

    return 0;
}