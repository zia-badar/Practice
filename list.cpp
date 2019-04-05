#include <iostream>

using namespace std;

template<typename type>
class list
{
    public: class iterator;

    private:
        struct node
        {
            type data;
            node* next;
            node* previous;
        };

        node* head;
        node* tail;

    public:

        class iterator
        {
            public:
                iterator(){}

                const type& operator*(){return current->data;}
                bool operator==(iterator iter){return current == iter.current;}
                bool operator!=(iterator iter){return current != iter.current;}
                const iterator& operator++()
                {
                    if(current->next == NULL) throw "out of bound exception";
                    current = current->next;
                    return *this;
                }
                const iterator& operator++(int)
                {
                    iterator tmp(*this);
                    operator++();
                    return tmp;
                }

                private:
                    node* current;

                    iterator(node *n) : current(n) {}
                    node* get_current(){return current;}

                    friend class list;
        };

        list()
        {
            head = new node();
            tail = new node();
            head->previous = NULL;
            head->next = tail;
            tail->previous = head;
            tail->next = NULL;
        }

        void add(type data)
        {
            node *n = new node;
            n->data = data;
            n->previous = tail->previous;
            n->next = tail;
            tail->previous->next = n;
            tail->previous = n;
        }

        void remove(int ind)
        {
            node* iter = head->next;
            for(int i=0; i<ind && iter != tail; i++, iter = iter->next);

            if(iter == tail) throw "Index out of bound exception";

            node* tmp = iter->previous;
            iter->previous->next = iter->next;
            iter->next->previous = tmp;
        }

        type& operator[](int ind)
        {
            node* iter = head->next;
            for(int i=0; i<ind && iter != tail; iter = iter->next, i++);

            if(iter == tail) throw "Index out of bound exception";
            return iter->data;
        }

        // deep copy
        list& operator+=(const list<type> &l)
        {
            for(node *n = l.head->next; n != l.tail; n = n->next)
                add(n->data);
            return *this;
        }

        friend ostream& operator<<(ostream& out, const list<type> &l)
        {
            out << '[';
            for(node* n = l.head->next; n != l.tail; n = n->next)
                out << n->data << (n->next == l.tail ? "" : ", ");
            out << "]\n";
            return out;
        }

        void clear()
        {
            head->next = tail;
            tail->previous = head;
        }

        iterator begin(){return *(new iterator(head->next));}
        iterator end(){return *(new iterator(tail));}

};

int main()
{
    list<int> l, l2;

    //-------------------------------------------------------------------------------
    cout << "add opeartion\n";
    for(int i=0; i<10; i++) l.add(i);
    cout << l << "\n\n\n";
    l.clear();
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    cout << "remove opeartion\n";
    for(int i=0; i<10; i++) l.add(i);
    for(int i=0; i<5; i++) l.remove(i);
    cout << l << "\n\n\n";
    l.clear();
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    cout << "ith element access opeartion\n";
    for(int i=0; i<10; i++) l.add(i);
    for(int i=0; i<10; i++) cout << l[i] << (i == 9 ? "\n\n\n" : ", ");
    l.clear();
    //-------------------------------------------------------------------------------


    //-------------------------------------------------------------------------------
    cout << "combining lists opeartion\n";
    for(int i=0; i<10; i++) l.add(i);
    for(int i=10; i<20; i++) l2.add(i);
    l += l2;
    cout << l << "\n\n\n";
    l.clear();
    l2.clear();
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    cout << "iterator opeartion\n";
    for(int i=0; i<10; i++) l.add(i);
    list<int>::iterator iter;
    for(iter = l.begin(); iter != l.end(); iter++)
         cout << *iter << ", ";
    cout << "\n\n\n";
    l.clear();
    //-------------------------------------------------------------------------------

    return 0;
}