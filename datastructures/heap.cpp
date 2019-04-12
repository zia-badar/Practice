#include <iostream>
#include <cstdlib>

using namespace std;

template<typename type>
class heap
{
    #define parent(i) (i == 0 ? -1 : (i%2 ? (i-1)/2 : (i-2)/2))
    #define left(i) (i*2+1)
    #define right(i) (i*2+2)

    public:
        heap(){allocate_array();}
        int size;
        int max_size;

        void add(type &v)
        {
            if(size == max_size) resize(max_size*2);
            array[size++] = &v;
            for(int i=size-1; parent(i) != -1 && array[parent(i)] > array[i]; i=parent(i))    // pushing up
                swap(parent(i), i);
        }

        type& remove()
        {
            if(size == 0) throw "heap empty exception";
            type *ret = array[0];
            array[0] = array[--size];
            for(int i=0; left(i)<size && right(i)<size && (array[left(i)] < array[i] || array[right(i)] < array[i]); )  // pushing down
                if (array[left(i)] < array[right(i)])
                {
                    swap(left(i), i);
                    i=left(i);
                }
                else
                {
                    swap(right(i), i);
                    i=right(i);
                }
            return *ret;
        }

    private:
        type **array;   // an array of pointers

        void allocate_array(int s=1024)
        {
            size = 0;
            max_size = s;
            array = new type*[max_size];
        }

        void resize(int new_size)
        {
            int **new_array = new type*[new_size];
            for(int i=0; i<max_size; i++) new_array[i] = array[i];
            max_size = new_size;
            array = new_array;
        }

        void swap(int i1, int i2)
        {
            type *p = array[i1];
            array[i1] = array[i2];
            array[i2] = p;
        }

        friend ostream& operator<<(ostream& out, const heap &h)
        {
            for(int i=0, j=0; i<h.size; i++)
                if(i==j)
                {
                    out << *h.array[i] << "\n";
                    j = j*2+2;
                }
                else out << *h.array[i] << ", ";

            out << "\n";
            return out;
        }
};

int main()
{
    heap<int> h;
    int size = 1024;
    int arr[size];


    for (int i = size; i > 0; i--)
        h.add(arr[i] = i);

    cout << "heap: \n" << h;

    cout << "removed elements: ";
    for (int i = 0; i < size; i++)
        cout << h.remove() << ((i==size-1) ? "" : ", ");

    return 0;
}