#include <iostream>

#include "../../problems/problem3.h"

using namespace std;

int main()
{
    int array[] = {1, 3, 7, 9, 10, 11};
    int sum = 7;
    cout << count(array, 6, sum) << endl;

    int array2[] = {1, 2, 3, 4, 5, 6, 7, 8};
    sum = 7;
    cout << count(array2, 8, sum) << endl;

    return 0;
}