#ifndef  BINOMIAL_HEAP_H
#define  BINOMIAL_HEAP_H

#include <climits>

template<typename data>
class binomial_heap
{
    class node;

    // represents the first(largest degree) heap in list of heaps.
    node* first;
    // represents the last(smallest degree) heap in list of heaps.
    node* last;
    // represents the heap with the smallest value root.
    node* smallest;

    class node
    {
        public:
            data* d;
            node* parent;
            node* next_sibling;
            node* previous_sibling;
            node* child;    // child points to the largest degree child, next sibling point to lower degree child
            int degree;     // meaning childrens are arranged in higher to lower degree order.

            node(data &d_): d(&d_), parent(NULL), next_sibling(NULL), previous_sibling(NULL), child(NULL), degree(0){}
    };


    //  function takes two lists of heaps in order of higher to lower degree, both initially pointing to the lowest
    //  degree node of the list and merge them into one list of heaps, it is like adding two binary numbers
    //  which are represented as list of positions where there are 1's
    node* merge_list_heap(node* list1, node* list2)
    {
        node* new_list = NULL;
        node* carry = NULL;
        while((list1 != NULL && list2 != NULL) || ((list1 != NULL || list2 != NULL) && carry != NULL))
        {
            node* lp1 = list1 != NULL ? list1->previous_sibling : NULL;
            node* lp2 = list2 != NULL ? list2->previous_sibling : NULL;
            if(list1 != NULL && list2 != NULL && list1->degree == list2->degree)
            {
                if(carry != NULL) add_before(carry, new_list);
                carry = merge_trees(list1, list2);
                list1 = lp1;
                list2 = lp2;
            }
            else
            {
                node* smaller = (list1 != NULL ? list1->degree : INT_MAX) < (list2 != NULL ? list2->degree : INT_MAX) ? list1 : list2;

                if(carry == NULL) add_before(smaller, new_list);
                else if(carry->degree == smaller->degree) carry = merge_trees(carry, smaller);
                else
                {
                    add_before(carry, new_list);
                    carry = NULL;
                    add_before(smaller, new_list);
                }

                if(smaller == list1) list1 = lp1;
                else list2 = lp2;
            }
        }
        node* remaining = carry != NULL ? carry : (list1 != NULL ? list1 : (list2 != NULL ? list2 : NULL));
        if(remaining != NULL)
        {
            remaining->next_sibling = new_list;
            if(new_list != NULL) new_list->previous_sibling = remaining;
            else new_list = remaining;
        }

        if(new_list != NULL)
            while(new_list->previous_sibling != NULL) new_list = new_list->previous_sibling;

        return new_list;
    }

    // unused connections are set to NULL to prevent unexpected behaviour when traversing
    void add_before(node* a, node* &b)
    {
        a->next_sibling = b;
        if(b != NULL) b->previous_sibling = a;      // b could be null but a is gurrentied not to be null
        a->previous_sibling = NULL;
        b = a;
    }

    // merges two heaps, heap with smaller root becomes parent of larger one.
    // unused connections are set to NULL to prevent unexpected behaviour when traversing
    node* merge_trees(node* t1, node* t2)
    {
        node *smaller = t1, *larger = t2;
        if(*t1->d > *t2->d)
        {
            smaller = t2;
            larger = t1;
        }

        larger->next_sibling = smaller->child;
        if(smaller->child != NULL) smaller->child->previous_sibling = larger;
        smaller->child = larger;
        larger->previous_sibling = NULL;

        smaller->previous_sibling = smaller->next_sibling = NULL;
        smaller->degree++;
        return smaller;
    }

    public:
        binomial_heap(): first(NULL), last(NULL), smallest(NULL) {}

        // O(log(n)), O(1) amotized
        void push(data &d)
        {
            node* new_node = new node(d);
            node* n = last;
            while(n != NULL && n->degree == new_node->degree)
            {
                node* tmp = n->previous_sibling;
                new_node = merge_trees(n, new_node);
                n = tmp;
            }
            smallest = smallest == NULL || *new_node->d < *smallest->d ? new_node : smallest;
            new_node->previous_sibling = n;
            if(n != NULL) n->next_sibling = new_node;
            else first = new_node;
            last = new_node;
        }

        // O(log(n))
        data* pop()
        {
            if(smallest == NULL) return NULL;                               // empty heap

            if(smallest == first) first = smallest->next_sibling;   // disconnecting heap with smallest root from list
            if(smallest == last) last = smallest->previous_sibling; // of heaps
            if(smallest->previous_sibling != NULL) smallest->previous_sibling->next_sibling = smallest->next_sibling;
            if(smallest->next_sibling != NULL) smallest->next_sibling->previous_sibling = smallest->previous_sibling;

            node* list1 = last;
            node* list2 = smallest->child;
            while(list2 != NULL && list2->next_sibling != NULL) list2 = list2->next_sibling;

            node* merged_list = merge_list_heap(list1, list2);  // merging child heaps of smallest root heap with
                                                                // with remaining heaps
            data* ret = smallest->d;
            delete smallest;

            if(merged_list != NULL)
            {
                first = merged_list;
                smallest = first;
                while(merged_list->next_sibling != NULL)
                {
                    merged_list = merged_list->next_sibling;
                    smallest = *smallest->d > *merged_list->d ? merged_list : smallest;
                }
                last = merged_list;
            }
            else first = last = smallest = NULL;

            return ret;
        }

        // todo decrease value function
};

#endif