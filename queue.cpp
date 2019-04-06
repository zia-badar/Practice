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
                node(type &d): data(d), next(NULL){}
                node(type &d, node *n): data(d), next(n){}
                type& data;
                node* next;
        };

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

int main()
{
    queue<int> q;
    int arr[10];
    for (int i = 0; i < 10; i++)    // literal cannot be passed i.e q.enqueue(1), passed value need to have memory allocated
        q.enqueue(arr[i] = i);      // because queue only maintains reference to initialized data but donot allocates it.
     cout << "queue: " << q;        // if the passed value is defined inside loop then once the next loop iteration starts
                                    // the value will get uninitialized because of out of scope and will get overwritten.

    for(int i=0; i<5; i++)
        cout << "dequeued: " << q.dequeue() << "\n";

    cout << "queue after dequeuing" << q;

    return 0;
}
