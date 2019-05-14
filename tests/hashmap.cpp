#include "../datastructures/hashmap.h"

// address of key is considered as its hash
uintptr_t simple_hash_function(const int &k) {return reinterpret_cast<uintptr_t>(&k);}

int main()
{
    hashmap<int, int> hmap(hashmap<int, int>::separate_chaining, simple_hash_function);
    int size = 2048;
    int keys[size], values[size];
    for (int i=0; i<size; i++)
    {
        keys[i] = i;
        values[i] = i*10;
    }
    for (int i = 0; i < size; i++)
        hmap.add(keys[i], values[i]);
    cout << hmap;

    return 0;
}
