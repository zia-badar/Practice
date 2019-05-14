#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

template<typename type>
class stack
{
    private:
        class node
        {
            public:
                node(): next(NULL){}
                node(type &d): data(d), next(NULL){}
                node(type &d, node *n): data(d), next(n){}
                type &data;
                node* next;
        };

        node* head;
    public:
        stack(): head(NULL){}
        void push(type &data)
        {
            node* n = new node(data);
            n->next = head;
            head = n;
        }

        type& pop()
        {
            node *n = head;
            type &v = head->data;
            head = head->next;
            delete n;
            return v;
        }

        friend ostream& operator<<(ostream& out, const stack& s)
        {
            out << '[';
            for(node *n = s.head; n != NULL; n = n->next)
                out << n->data << (n->next == NULL ? "" : ", ");
            out << "]\n";
            return out;
        }

        ~stack()
        {
            while(head != NULL)
            {
                node *t = head;
                head = head->next;
                delete t;
            }
        }
};

#endif
