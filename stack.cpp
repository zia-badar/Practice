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
                node(type d): data(d), next(NULL){}
                node(type d, node *n): data(d), next(n){}
                type data;
                node* next;

                ~node() {delete next;}
        };

        node* head;
    public:
        stack(): head(NULL){}
        void push(type data)
        {
            node* n = new node(data);
            n->next = head;
            head = n;
        }

        type& pop()
        {
            type &tmp = head->data;
            head = head->next;
            return tmp;
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
    for(int i=0; i<10; i++)
        s.push(i);
    cout << "stack: " << s;

    for(int i=0; i<5; i++)
        cout << "pop: " << s.pop() << "\n";

    cout << "stack after pop: " << s;

    return 0;
}
