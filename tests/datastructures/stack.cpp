#include "../../datastructures/stack.h"

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