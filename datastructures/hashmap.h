#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <cmath>

using namespace std;

template <typename key, typename value>
class hashmap
{

    public:
        class pair
        {
            public:         // to do remove from public
                pair *next;     // used only for separte chaining

            public:
                key &first;
                value &second;
                pair(): first(0), second(NULL), next(NULL) {}
                pair(key &k, value &v): first(k), second(v), next(NULL) {}
                friend ostream& operator<<(ostream& out, const pair &p) {out << "(" << p.first << ", " << p.second << ")"; return out;}

            friend class hashmap;
        };
        enum collision_resolve {rehashing, linear_probing, quadratic_probing, separate_chaining};

        hashmap(uintptr_t(*f)(const key&)): collision_resolving_technique(rehashing), hash_function(f) {allocate_array();}
        hashmap(collision_resolve crt, uintptr_t (*f)(const key&)): collision_resolving_technique(crt), hash_function(f) {allocate_array();}

        bool add(key &k, value &v)
        {
            int hash;
            switch(collision_resolving_technique)
            {
                case rehashing:
                    hash = hash_function(k) % size;
                    if(array[hash] != NULL)
                    {
                        rehash(size*2);
                        hash = hash_function(k) % size;
                        if(array[hash] != NULL)
                        {
                            rehash(size/2);
                            return false;
                        }
                    }
                    array[hash] = new pair(k, v);
                    return true;
                break;
                case linear_probing:
                    hash = hash_function(k) % size;
                    if(array[hash] != NULL)
                    {
                        for (; hash<size && array[hash]!=NULL; hash++);
                        if(hash == size) return false;
                    }
                    array[hash] = new pair(k, v);
                    return true;
                break;
                case quadratic_probing:
                    hash = hash_function(k) % size;
                    if(array[hash] != NULL)
                    {
                        int i;
                        for (i=1; i < sqrt(size) && array[(hash+i*i)%size]==NULL; i++);
                        if(i == sqrt(size)) return false;
                        hash = (hash+i*i)%size;
                    }
                    array[hash] = new pair(k, v);
                    return true;
                break;
                case separate_chaining:
                    hash = hash_function(k) % size;
                    if(array[hash] == NULL)
                        array[hash] = new pair(k, v);
                    else
                    {
                        int chain_size = compute_chain_size(array[hash]);
                        if(chain_size > size)
                            rehash(size*2);
                        chain_size = compute_chain_size(array[hash]);
                        if(chain_size > size)
                        {
                            rehash(size/2);
                            return false;
                        }
                        hash = hash_function(k) % size;
                        get_last_in_chain(array[hash])->next = new pair(k, v);
                    }
                    return true;
                break;
            }
        }

    private:
        pair **array;           // this is an array of pointers; not to be confused with 2d array
        collision_resolve collision_resolving_technique;
        uintptr_t (*hash_function)(const key&);
        int size;

        int compute_chain_size(pair *p)
        {
            int i=0;
            for(; p!=NULL; p=p->next);
            return i;
        }
        pair* get_last_in_chain(pair *p)
        {
            for(; p->next!=NULL; p=p->next);
            return p;
        }

        void rehash(int new_size)                       // if new size is an increment of old size then possiblity
        {                                               // of new hash map introducing collisions which were not
            pair **new_array = new pair*[new_size];     // in old hash map is present. This will not happen if new
            int hash;                                   // size is a multiple of old size
            for(int i=0; i<new_size; i++) new_array[i] = NULL;
            for(int i=0; i<size; i++)
                if(array[i] != NULL)
                {
                    pair *p = array[i];
                    for(; p != NULL; p=p->next)
                    {
                        hash = hash_function(p->first) % new_size;
                        new_array[hash] = p;
                    }
                }

            delete array;               // pairs pointed by old array are not deleted and are pointed by new_array only
            size = new_size;            // the array is deleted
            array = new_array;
        }

        void allocate_array(int s=1024)
        {
            size = s;
            array = new pair*[size];
            for(int i=0; i<size; i++) array[i] = NULL;
        }

        friend ostream& operator<<(ostream& out, const hashmap &map)
        {
            pair *p;
            for(int i=0; i<map.size; i++)
                if(map.array[i] != NULL)
                {
                    out << '[' << i << ']';
                    p = map.array[i];
                    for(; p != NULL; p=p->next)
                        out << "->" << *p << (p->next == NULL ? "\n" : "");
                }
            return out;
        }
};

#endif
