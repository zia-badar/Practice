#include <iostream>

using namespace std;

template<typename type>
class queue
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
        node* tail;

    public:
        queue(): head(NULL), tail(NULL){}
        void enqueue(type data)
        {
            if (head == NULL)
                head = tail = new node(data);
            else
            {
                tail->next = new node(data);
                tail = tail->next;
            }
        }

        type& dequeue()     // node is not deleted because data inside node can still be in use by dequeue calling code.
        {
            type &tmp = head->data;
            head = head->next;
            return tmp;
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

int main()
{
    queue<int> q;
    for(int i=0; i<10; i++)
        q.enqueue(i);
    cout << "queue: " << q;

    for(int i=0; i<5; i++)
        cout << "dequeued: " << q.dequeue() << "\n";

    cout << "queue after dequeuing" << q;

    return 0;
}
