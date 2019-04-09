#include <iostream>

using namespace std;

template<typename type>
class linklist
{
    public: class iterator;

    private:
        class node
        {
            public:
                type* data;             // pointer is used not because the data will get change inside node because
                node* next;             // it will not, it is used because head and tail donot have data and if
                node* previous;         // reference is used then head and tail need to be assigned some reference,
                                        // with pointer data inside head and tail is null
                node(): data(NULL), next(NULL), previous(NULL) {}
        };

        node* head;
        node* tail;

    public:

        class iterator
        {
            public:
                iterator(): current(NULL) {}
                const type& operator*(){return *current->data;}
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
                    iterator &tmp = *this;
                    operator++();
                    return tmp;
                }

                private:
                    node* current;
                    iterator(node *n): current(n) {}

                    friend class linklist;
        };

        linklist()
        {
            head = new node();
            tail = new node();
            head->previous = NULL;
            head->next = tail;
            tail->previous = head;
            tail->next = NULL;
        }

        void add(type &data)
        {
            node *n = new node();
            n->data = &data;
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
            delete iter;
        }

        type& operator[](int ind)
        {
            node* iter = head->next;
            for(int i=0; i<ind && iter != tail; iter = iter->next, i++);

            if(iter == tail) throw "Index out of bound exception";
            return *iter->data;
        }

        // shallow copy of data inside passed list
        linklist& operator+=(const linklist<type> &l)
        {
            for(node *n = l.head->next; n != l.tail; n = n->next)
                add(*n->data);
            return *this;
        }

        friend ostream& operator<<(ostream& out, const linklist<type> &l)
        {
            out << '[';
            for(node* n=l.head->next; n!=l.tail; n=n->next)
                out << *n->data << (n->next == l.tail ? "" : ", ");
            out << "]\n";
            return out;
        }

        void clear()
        {
            for(node *n=head->next; n!=tail; n=n->next) delete n;
            head->next = tail;
            tail->previous = head;
        }

        iterator begin(){return iterator(head->next);}
        iterator end(){return iterator(tail);}

        ~linklist(){delete head; delete tail;}

};

int main()
{
    linklist<int> l, l2;
    int size = 10;
    int arr[size];
    int arr2[size];

    //-------------------------------------------------------------------------------
    cout << "add opeartion\n";
    for(int i=0; i<size; i++) l.add(arr[i]=i);
    cout << l << "\n\n\n";
    l.clear();
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    cout << "remove opeartion\n";
    for(int i=0; i<size; i++) l.add(arr[i]=i);
    for(int i=0; i<size/2; i++) l.remove(i);
    cout << l << "\n\n\n";
    l.clear();
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    cout << "ith element access opeartion\n";
    for(int i=0; i<size; i++) l.add(arr[i]=i);
    for(int i=0; i<size; i++) cout << l[i] << (i == 9 ? "\n\n\n" : ", ");
    l.clear();
    //-------------------------------------------------------------------------------


    //-------------------------------------------------------------------------------
    cout << "combining linklists opeartion\n";
    for(int i=0; i<size; i++) l.add(arr[i]=i);
    for(int i=0; i<size; i++) l2.add(arr2[i]=size+i);
    l += l2;
    cout << l << "\n\n\n";
    l.clear();
    l2.clear();
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    cout << "iterator opeartion\n";
    for(int i=0; i<10; i++) l.add(arr[i]=i);
    for(linklist<int>::iterator iter = l.begin(); iter != l.end(); iter++)
         cout << *iter << ", ";
    cout << "\n\n\n";
    l.clear();
    //-------------------------------------------------------------------------------

    return 0;
}