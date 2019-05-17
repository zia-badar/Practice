#include <iostream>
#include <queue>
#include "../datastructures/dynamic_heap.h"

using namespace std;

class djikstra
{
    public:
        class node
        {
            int data;
            vector<pair<node*, int>> adjacency_list;
        };

        void solve(node* src)
        {

        }

};

class class_
{
    public:
        int i;
        friend bool operator< (const class_& obj1, const class_& obj2)
        {
            return obj1.i > obj2.i;
        }

        friend ostream& operator<<(ostream& out, class_& obj)
        {
            out << to_string(obj.i) << endl;
            return out;
        }
};

int main()
{
    dynamic_heap<int> heap;
    int size = 1024;
    int arr[size];
    for(int i=0; i<size; i++)
        heap.add(arr[i] = i);
    for(int i=0; i<size; i++)
        heap.decrease_entry(arr[i], 2*i);
    cout << heap << endl;
    for(int i=0; i<size; i++)
        cout << heap.remove() << endl;

    return 0;
}