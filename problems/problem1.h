// Converting a number of size n to largest palaindrom by replacing k characters

#ifndef PROBLEM_1_H
#define PROBLEM_1_H

#include <list>
#include <algorithm>

using namespace std;

void solve(string &num, int k)     // assuming k will be sufficient to construct palaindrom
{
    list<int> l;                        // keeps record of digits changed
    for(int i=0; i<num.size()/2 && k>0; i++)       // setting different digits on both sides to max of each other
        if(num[i] != num[num.size()-1-i])
        {
            char a = max(num[i], num[num.size()-1-i]);
            num[i] = max(num[i], num[num.size()-1-i]);
            num[num.size()-1-i] = max(num[i], num[num.size()-1-i]);
            k--;
            l.push_back(i);
        }

    for(int i=0; i<num.size()/2 && k>0; i++)
        if(!l.empty() && l.front() == i)        // setting different digits to 9, which were changed before so
        {                                       // k is decrease only by 1
            num[i] = '9';
            num[num.size()-1-i] = '9';
            k--;
            l.pop_front();
        }
        else if(k >= 2)                         // setting different digits to 9, k is decrease only by 2
        {                                       // because these digits were not changed before
            num[i] = '9';
            num[num.size()-1-i] = '9';
            k -= 2;
        }

    if(k > 0 && num.size() % 2 == 1)            // for odd size array, checking middle element
        num[num.size()/2] = '9';
}


#endif