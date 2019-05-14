#include "../datastructures/queue.h"

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
