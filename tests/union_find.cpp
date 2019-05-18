#include <iostream>

#include "../algorithms/union_find.h"

using namespace std;

int main()
{
    union_find uf(10);
    for(int i=0; i<5; i++)
    {
        cout << "connecting " << i*2 << " " << i*2+1 << endl;
        uf.connect(i*2, i*2+1);
    }

    for(int i=0; i<10; i++)
        for(int j=0; j<10; j++)
            if(i != j && uf.are_connected(i, j))
                cout << i << " " << j << " are connected\n";

    return 0;
}
