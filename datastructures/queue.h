#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

using namespace std;

template<typename type>
class queue
{
    private:
        class node
        {
            public:
                node(type &d): data(d), next(NULL){}
                node(type &d, node *n): data(d), next(n){}
                type& data;                                     // reference is used because data inside node will
                node* next;                                     // never change and we have no node with null value of
        };                                                      // data

        node* head;
        node* tail;

    public:
        queue(): head(NULL), tail(NULL){}
        void enqueue(type &data)
        {
            if (head == NULL)
                head = tail = new node(data);
            else
            {
                tail->next = new node(data);
                tail = tail->next;
            }
        }

        type& dequeue()
        {
            node *n = head;
            type &v = head->data;
            head = head->next;
            delete n;
            return v;
        }

        friend ostream& operator<<(ostream& out, const queue& s)
        {
            out << '[';
            for(node *n = s.head; n != NULL; n = n->next)
                out << n->data << (n->next == NULL ? "" : ", ");
            out << "]\n";
            return out;
        }

        ~queue()
        {
            while (head != NULL)
            {
                node *t = head;
                head = head->next;
                delete t;
            }
        }
};

#endif
