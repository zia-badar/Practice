#include <iostream>

using namespace std;

// it is a min heap implementation without using array because of which size is dynamic, it uses pointers to represent heap
template<typename type>
class dynamic_heap
{
    private:
        class node
        {
            public:
                node* parent;
                node* left;
                node* right;
                node* previous; // it represents the previous node in heap tree in top to bottom, left to right order
                node* next;     // it represents the next node in heap tree in top to bottom, left to right order
                type *data;

                node(): parent(NULL), left(NULL), right(NULL), previous(NULL), next(NULL) {};
                node(type *d): parent(NULL), left(NULL), right(NULL), previous(NULL), next(NULL), data(d) {};
        };

        node* root; // it represent the first node in heap from top to bottom, left to right.
        node* last; // it represent the last node in heap from top to bottom, left to right.
        node* last_parent;   // it represent the first node who has less than two childern when going from top to bottom, left to right.

    public:

        dynamic_heap(): root(NULL), last(NULL), last_parent(NULL) {};

        void add(type& data)
        {
            node* n = new node(&data);

            if(last_parent == NULL)
            {
                root = last_parent = last = n;
                return;
            }

            n->previous = last;                                 // connect to last node
            last->next = n;
            last = n;                                           // update last node to new node

            if(last_parent->left == NULL)
            {
                last_parent->left = n;    // connect new node to last parent
                n->parent = last_parent;
            }
            else if(last_parent->right == NULL)             // if right is consumed of last parent then update
            {                                               // last parent to point to next node of no childrens.
                last_parent->right = n;
                n->parent = last_parent;
                last_parent = last_parent->next;
            }

            while(n->parent != NULL && n->parent->data > n->data)    // pushing up
            {
                type *t = n->parent->data;
                n->parent->data = n->data;
                n->data = t;
                n = n->parent;
            }
        }

        type& remove()
        {
            if(root == NULL) throw "heap empty exception";
            type* d = root->data;

            if(last_parent == NULL)             // if only one entry exists in heap
            {
                delete root;
                root = last_parent = last = NULL;
                return *d;
            }

            if(last->parent->left == last)              // if last entry is left child, disconnect it from its parent
            {                                           // and update last parent to point to previous node in
                last_parent->left = NULL;               // top to bootom left to right order
                last_parent = last_parent->previous;
            }
            else
            {
                last_parent->right = NULL;              // disconnect last from its parent
            }

            last->previous->next = NULL;                // disconnect from second last node
            root->data = last->data;                    // swap data from last node to root

            node* old_last = last;
            last = last->previous;                      // updating last node
            delete old_last;                            // deleting last node

            node *n = root;                             // pushing down
            while((n->left != NULL && *n->data > *n->left->data) || (n->right != NULL && *n->data > *n->right->data))
                if(*n->left->data < *n->right->data)
                {
                    type* t = n->data;
                    n->data = n->left->data;
                    n->left->data = t;
                    n = n->left;
                }
                else
                {
                    type* t = n->data;
                    n->data = n->right->data;
                    n->right->data = t;
                    n = n->right;
                }

            return *d;
        }
};

int main()
{
    dynamic_heap<int> heap;
    int size = 1024;
    int arr[size];


    for (int i = size; i > 0; i--)
        heap.add(arr[i] = i);


    cout << "removed elements: ";
    for (int i = 0; i < size; i++)
        cout << heap.remove() << ((i==size-1) ? "" : ", ");


    return 0;
}
