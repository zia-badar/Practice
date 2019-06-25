#ifndef PROBLEM_5_H
#define PROBLEM_5_H

#include <iostream>

using namespace std;

int **memo;

int longest_nonoverlapping_repeating_substring(string str, int i, int j)
{
    if(i == str.length() || j == str.length()) return 0;
    if(memo[i][j] != -1) return memo[i][j];

    int max = 0;
    int tmp;
    if(i != j && str[i] == str[j])
    {
        tmp = longest_nonoverlapping_repeating_substring(str, i+1, j+1);
        int diff = abs(j-i);
        max = 1 + (diff < tmp ? diff : tmp);
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


    int max = 0;
    int tmp;
    for(int i=0; i<str.length(); i++)
        for(int j=i+1; j<str.length(); j++)
        {
            tmp = longest_nonoverlapping_repeating_substring(str, i, j);
            max = max < tmp ? tmp : max;
        }


    //----------------------------- memory deallocation ----------------------------------------------
    for(int i=0; i<str.length(); i++)
        delete [] memo[i];
    delete [] memo;
    //-------------------------------------------------------------------------------------------------

    return max;
}


#endif