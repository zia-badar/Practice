#include <iostream>
#include <time.h>
#include "../algorithms/sorting.h"
#include "../algorithms/order_statistic.h"

using namespace std;

int main()
{
    srand(time(NULL));

    int size = 10;
    int sorted[size], unsorted[size];

    for(int i=0; i<size; i++)
        sorted[i] = unsorted[i] = i;

    unsort(unsorted, size, swap);

    for(int i=0; i<size; i++)
        cout << sorted[i] << " " << get_kth_smallest(unsorted, 0, size-1, i, swap) << endl;
}