#include <time.h>

// kth smallest element in linear time
template<typename data_type>
data_type get_kth_smallest(data_type* array, int l, int r, int k, void (*swap)(data_type&, data_type&))
{
    int ran = rand() % (r-l+1) + l;
    swap(array[r], array[ran]);
    int j=l;
    for(int i=l; i<r; i++)
        if(array[i] < array[r])
            swap(array[i], array[j++]);
    swap(array[r], array[j]);

    if(j-l == k)
        return array[j];
    else if(j-l < k)
        return get_kth_smallest(array, j+1, r, k-(j-l+1), swap);
    return get_kth_smallest(array, l, j-1, k, swap);
}
