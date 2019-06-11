// Converting a number of size n to largest palaindrom by replacing k characters
#include <iostream>

#include "../../problems/problem1.h"

using namespace std;

int main()
{
    string num = "43435";
    int k = 3;
    solve(num, k);
    cout << num << endl;

    return 0;
}