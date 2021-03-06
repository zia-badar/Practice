#ifndef BINARY_INDEX_TREE_H
#define BINARY_INDEX_TREE_H

#include <iostream>
using namespace std;

template<typename result_type, typename data_type>
class bit
{
    private:
        result_type *array;
        int size;

    public:
        bit(): array(NULL), size(0) {}

        void build(data_type *arr, int s, result_type (*combine)(result_type, result_type), result_type (*split)(result_type, result_type),
                result_type (*map)(data_type), result_type empty)
        {
            size = s;
            array = new result_type[size+1];
            result_type tmp[size+1];
            array[0] = tmp[0] = empty;

            int lastn;
            for(int i=1; i<=size; i++)
            {
                tmp[i] = combine(tmp[i-1], map(arr[i]));
                lastn = i - (i & ~(i-1));
                array[i] = split(tmp[i-1], tmp[lastn - (lastn == 0 ? 0 : 1)]);
            }
        }

        result_type query(int f, int t, result_type (*combine)(result_type, result_type), result_type (*split)(result_type, result_type), result_type empty)
        {
            f++; t++;                               // index to position conversion
            result_type res1=empty, res2=empty;
            for(int i=t; i>0; i= i - (i & ~(i-1)))
                res1 = combine(array[i], res1);
            for(int i=f-1; i>0; i= i - (i & ~(i-1)))
                res2 = combine(array[i], res2);
            return split(res1, res2);
        }


        friend ostream& operator<<(ostream &out, const bit &t)
        {
            for(int i=0; i<t.size+1; i++)
                out << t.array[i] << (i == t.size ? "\n" :", ");
            return out;
        }
};

// range sum functions, empty value is 0
int combine_function1(int s1, int s2) { return s1 + s2; }
int split_function1(int s1, int s2){ return s1 - s2; }
int map_function1(int i){ return i; }

string combine_function2(string s1, string s2) { return s1 + s2; }
string split_function2(string s1, string s2)
{
    if(s1.find(s2) == 0) s1.erase(0, s2.length());
    return s1;
}
string map_function2(int i){ return "-" + to_string(i) + "-"; }

#endif
