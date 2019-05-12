#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

template<typename data_type>
void selection_sort(data_type *arr, int size, void (*swap)(data_type&, data_type&), int (*compare)(const data_type&, const data_type&))
{
    int min;
    for(int i=0; i<size-1; i++)
    {
        min=i;
        for(int j=i+1; j<size; j++)
            if(compare(arr[j], arr[min]) == -1)
                min = j;

        swap(arr[i], arr[min]);
    }
}

template<typename data_type>
void insertion_sort(data_type *arr, int size, int (*compare)(const data_type&, const data_type&))
{
    int tmp;
    for(int i=1; i<size; i++)
    {
        tmp = arr[i];
        int j;
        for(j=i-1; j>=0 && compare(tmp, arr[j]) == -1; arr[j+1]=arr[j], j--);
        arr[j+1] = tmp;
    }
}

template<typename data_type>
void merge_sort(data_type *arr, int l, int r)
{
    if(l == r) return;
    merge_sort(arr, l, (l+r)/2);
    merge_sort(arr, (l+r)/2 + 1, r);

    // merge
    int s1=l, e1=(l+r)/2, s2=(l+r)/2+1, e2=r;
    int tmp[r-l+1];
    int i, j, k;
    for(i=s1, j=s2, k=0; i<=e1 && j<=e2;)
        if(arr[i] <= arr[j])
            tmp[k++] = arr[i++];
        else
            tmp[k++] = arr[j++];


    while(i <= e1)
        tmp[k++] = arr[i++];

    while(j <= e2)
        tmp[k++] = arr[j++];

    for(i=0; l+i<=r; i++)
        arr[l+i] = tmp[i];
}

template<typename data_type>
void quick_sort(data_type *arr, int l, int r, void (*swap)(data_type&, data_type&))
{
    if(l >= r) return;

    int i, j;
    for(i=l, j=l; i<r; i++)
        if(arr[i] < arr[r])
            swap(arr[i], arr[j++]);
    swap(arr[r], arr[j]);

    quick_sort(arr, l, j-1, swap);
    quick_sort(arr, j+1, r, swap);
}

#define nth_digit(i, n) ((i / (n != 1 ? (int)pow(10, (n-1)) : 1)) % 10)

void radix_sort(int *arr, int size)
{
    int largest_number_size = 0;
    for (int i = 0; i < size; i++)
    {
        int t = arr[i], l=0;
        while (t > 0)
        {
            t /= 10;
            l++;
        }
        if(l > largest_number_size) largest_number_size = l;
    }

    vector<int> sort_table[10];
    for(int i=0; i<size; i++) sort_table[0].push_back(arr[i]);

    for(int i=1; i<=largest_number_size; i++)
    {
        vector<int> tmp_table[10];

        for (int j=0; j<10; j++)
            for(int k=0; k<sort_table[j].size(); k++)
                tmp_table[nth_digit(sort_table[j][k], i)].push_back(sort_table[j][k]);

        for (int j=0; j<10; j++)
            sort_table[j] = tmp_table[j];
    }

    for (int i=0, k=0; i<10; i++)
        for(int j=0; j<sort_table[i].size(); j++)
            arr[k++] = sort_table[i][j];
}

template<typename data_type>
void unsort(data_type *arr, int size, void (*swap)(data_type&, data_type&))
{
    int tmp, random;
    for(int i=0; i<size; i++)
    {
        random = rand() % (size-i) + i;
        swap(arr[i], arr[random]);
    }
}

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

int compare(const int &a, const int &b)
{
    if(a < b) return -1;
    if(a > b) return 1;
    return 0;
}

int main()
{
    int size = 10;
    int array[size];
    for(int i=0; i<size; i++)
        array[i] = i;

    srand(time(NULL));

    unsort(array, size, swap);
    cout << "before sorting: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n" : ", ");
    selection_sort(array, size, swap, compare);
    cout << "after selection sort: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n\n" : ", ");

    unsort(array, size, swap);
    cout << "before sorting: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n" : ", ");
    insertion_sort(array, size, compare);
    cout << "after insertion sort: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n\n" : ", ");

    unsort(array, size, swap);
    cout << "before sorting: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n" : ", ");
    merge_sort(array, 0, size-1);
    cout << "after merge sort: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n\n" : ", ");

    unsort(array, size, swap);
    cout << "before sorting: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n" : ", ");
    quick_sort(array, 0, size-1, swap);
    cout << "after quick sort: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n\n" : ", ");

    unsort(array, size, swap);
    cout << "before sorting: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n" : ", ");
    radix_sort(array, size);
    cout << "after radix sort: ";
    for(int i=0; i<size; i++) cout << array[i] << (i==size-1 ? "\n\n" : ", ");

    return 0;
}