#ifndef PROBLEM_6_H
#define PROBLEM_6_H

#include <iostream>

using namespace std;

int **memo;

int longest_repeating_subsequence(string str, int i, int j)
{
    if(i == str.length() || j == str.length()) return 0;
    if(memo[i][j] != -1) return memo[i][j];

    int max = 0;
    if(i != j && str[i] == str[j])
        max = 1 + longest_repeating_subsequence(str, i+1, j+1);
    else
    {
        int tmp = longest_repeating_subsequence(str, i+1, j);
        max = max < tmp ? tmp : max;
        tmp = longest_repeating_subsequence(str, i, j+1);
        max = max < tmp ? tmp : max;
    }

    return (memo[i][j] = max);
}

// O(n^2)
int solve(string str)
{
    //---------------------------- memory allocation --------------------------------------------------
    memo = new int*[str.length()];
    for(int i=0; i<str.length(); i++)
        memo[i] = new int[str.length()];

    for(int i=0; i<str.length(); i++)
        for(int j=0; j<str.length(); j++)
            memo[i][j] = -1;
    //-------------------------------------------------------------------------------------------------

    int ret = longest_repeating_subsequence(str, 0, 0);

    //----------------------------- memory deallocation ----------------------------------------------
    for(int i=0; i<str.length(); i++)
        delete [] memo[i];
    delete [] memo;
    //-------------------------------------------------------------------------------------------------

    return ret;
}

#endif