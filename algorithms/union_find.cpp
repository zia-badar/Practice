#include <iostream>
#include <unordered_map>

using namespace std;

class union_find
{
    private:
        struct node
        {
            bool operator==(const node& that) { return this == &that; } // requirement of unorder map for comparasion
            size_t operator()(const node& key) // requirement of unordered map to convert key to hash
            {                                   //  it is a hash function
                cout << "hash function called\n";
                return 1;
            }
        };

    public:

        void test()
        {
            unordered_map<node, int, node> hash_map(100);
            node n;
            hash_map[n] = 1;
//            node n1, n2;
//            cout << (n1 == n2) << " " << (n1 == n1) << endl;
        }
};

int main()
{
//    unordered_map<int, int> hash_map(100, hash_function);
//    int arr[2];
//    arr[0]=7;
//    arr[1]=7;
//    hash_map[arr[0]] = 10;
//    hash_map[arr[1]] = 20;
//    cout << hash_map[7] << endl;

    union_find uf;
    uf.test();

    return 0;
}
