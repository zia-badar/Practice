#ifndef DYNAMIC_HEAP_H
#define DYNAMIC_HEAP_H

#include <iostream>
#include <unordered_map>
#include <sstream>

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
                type* data;

                node(): parent(NULL), left(NULL), right(NULL), previous(NULL), next(NULL), data(NULL) {};
                node(type *d): parent(NULL), left(NULL), right(NULL), previous(NULL), next(NULL), data(d) {};
                string to_string(string tab)
                {
                    ostringstream oss(ostringstream::ate);
                    oss << tab << "|--> data: ";
                    if(data != NULL) oss << *data << "\n";
                    tab += "\t";
                    if(left != NULL) oss << left->to_string(tab);
                    else oss << tab << "|-->" << "\n";
                    if(right != NULL) oss << right->to_string(tab);
                    else oss << tab << "|-->" << "\n";
                    return oss.str();
                }
                friend ostream& operator<<(ostream &out, node &n)
                {
                    out << n.to_string("");
                    return out;
                }
        };

        node* root; // it represent the first node in heap from top to bottom, left to right.
        node* last; // it represent the last node in heap from top to bottom, left to right.
        node* last_parent;   // it represent the first node who has less than two childern when going from top to bottom, left to right.
        unordered_map<type*, node*> map;  // it represent mapping from data to node in heap, used for decreasing a perticular data.

    public:

        dynamic_heap(): root(NULL), last(NULL), last_parent(NULL) {};

        // log(n)
        void add(type& data)
        {
            node* n = new node(&data);
            map[&data] = n;

            if(root == NULL)
            {
                n->previous = n->parent = NULL;
                root = last_parent = last = n;
                return;
            }

            n->previous = last;                                 // connect to last node
            last->next = n;
            last = n;                                           // update last node to new node

            if(last_parent->left == NULL)
            {
                last_parent->left = n;                      // connect new node to last parent
                n->parent = last_parent;
            }
            else if(last_parent->right == NULL)             // if right is consumed of last parent then update
            {                                               // last parent to point to next node of no childrens.
                last_parent->right = n;
                n->parent = last_parent;
                last_parent = last_parent->next;
            }

            push_up(n);
        }

        // log(n)
        type& remove()
        {
            if(root == NULL) throw "heap empty exception";
            type* d = root->data;
            node* old_last = last;

            if(last == root)                                // if only one entry exists in heap
                root = last_parent = last = NULL;
            else
            {
                if(last->parent->left == last)              // if last entry is right child, disconnect it from its parent
                    last->parent->left = NULL;              // and update last parent to point to previous node in
                else                                        // top to bootom left to right order
                {
                    last_parent = last_parent->previous;
                    last->parent->right = NULL;              // disconnect last from its parent
                }

                last->previous->next = NULL;                // disconnect last from second last node
                swap(root, last);                           // swap data from last node to root

                last = last->previous;                      // updating last node

                push_down(root);                            // pushing down
            }

            delete old_last;                            // deleting last node
            map.erase(d);
            return *d;
        }

        // log(n)
        void decrease_entry(type &data, type value)
        {
            if(map.find(&data) == map.end()) return;
            node* n = map.find(&data)->second;
            *n->data -= value;
            push_up(n);
        }

        void push_up(node* n)
        {
            while(n->parent != NULL && *n->parent->data > *n->data)    // pushing up
            {
                swap(n, n->parent);
                n = n->parent;
            }
        }

        void push_down(node* n)
        {
            while((n->left != NULL && *n->data > *n->left->data) || (n->right != NULL && *n->data > *n->right->data))
                if(n->right == NULL || *n->left->data < *n->right->data)
                {
                    swap(n, n->left);
                    n = n->left;
                }
                else
                {
                    swap(n, n->right);
                    n = n->right;
                }

        }

        // it swaps the data of two nodes and updates the hashmap of data to nodes.
        void swap(node* n1, node* n2)
        {
            type* t = n1->data;
            n1->data = n2->data;
            n2->data = t;
            map[n1->data] = n1;
            map[n2->data] = n2;
        }

        bool is_empty(){return root == NULL;}

        bool contains(type& data){return map.find(&data) != map.end();}

        friend ostream& operator<<(ostream &out, dynamic_heap& heap)
        {
            if(heap.root != NULL) out << *heap.root;
            return out;
        }
};

#endif
