#include <iostream>

#include "../../problems/problem4.h"

using namespace std;

int main()
{
    int array1[] = {1, 3, 5, 7};
    int array2[] = {2, 3, 5, 8};
    int sum = 10;
    cout << count(array1, 4, array2, 4, sum) << endl;

    int array3[] = {1, 2, 3, 4, 5, 7, 11};
    int array4[] = {2, 3, 4, 5, 6, 8, 12};
    sum = 9;
    cout << count(array3, 7, array4, 7, sum) << endl;

    return 0;
}