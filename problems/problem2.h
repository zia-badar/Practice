// finding minimum no of cuts to partition into palaindroms
#ifndef PROBLEM_2_H
#define PROBLEM_2_H

#include <iostream>
#include <climits>

using namespace std;

class palaindrom_partitioning
{
    enum result{FALSE, TRUE, UNCOMPUTED};
    result **palaindrom_possible;
    int *memo;

    // O(n^2)
    result is_palaindrom(string str, int i, int j)
    {
        if(palaindrom_possible[i][j] != UNCOMPUTED) return  palaindrom_possible[i][j];
        if(i == j) return (palaindrom_possible[i][j] = TRUE);               // odd lendth end case
        if(str[i] != str[j]) return (palaindrom_possible[i][j] = FALSE);    // if not similar
        if(i+1 == j) return (palaindrom_possible[i][j] = TRUE);            // if similar and even length end case
        return (palaindrom_possible[i][j] = is_palaindrom(str, i+1, j-1));  // if similar and decrease problem size
    }

    // O(n^2)
    int solve(string str, int p)
    {
        if(memo[p] != -1) return memo[p];

        int min = INT_MAX;
        for(int i=p; i<str.size(); i++)
            if(palaindrom_possible[p][i])
            {
                int tmp = i == str.size()-1 ? 0 : (solve(str, i+1) + 1);
                min = min > tmp ? tmp : min;
            }

        return (memo[p] = min);
    }


    public:
        int solve(string str)
        {
            palaindrom_possible = new result*[str.size()];
            for(int i=0; i<str.size(); i++) palaindrom_possible[i] = new result[str.size()];
            for(int i=0; i<str.size(); i++)
                for(int j=0; j<str.size(); j++)
                    palaindrom_possible[i][j] = UNCOMPUTED;
            for(int i=0; i<str.size(); i++)
                for(int j=i; j<str.size(); j++)
                    is_palaindrom(str, i, j);

            memo = new int[str.size()];
            for(int i=0; i<str.size(); i++) memo[i] = -1;

            int ret = solve(str, 0);

            for(int i=0; i<str.size(); i++) delete [] palaindrom_possible[i];
            delete [] palaindrom_possible;
            delete [] memo;

            return ret;
        }
};

#endif