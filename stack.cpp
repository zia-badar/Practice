#include <iostream>

using namespace std;

template<typename type>
class stack
{
    private:
        class node
        {
            public:
                node(): data(NULL), next(NULL){}
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

int main()
{
    stack<int> s;
    int arr[10];
    for(int i=0; i<10; i++)     // literal cannot be passed i.e s.push(1), passed value need to have memory allocated
        s.push(arr[i] = i);     // because stack only maintains reference to initialized data but donot allocates it.
    cout << "stack: " << s;     // if the passed value is defined inside loop then once the next loop iteration start
                                // the value will get uninitialized because of out of scope and will get overwritten.
    for(int i=0; i<5; i++)
        cout << "pop: " << s.pop() << "\n";

    cout << "stack after pop: " << s;

    return 0;
}
