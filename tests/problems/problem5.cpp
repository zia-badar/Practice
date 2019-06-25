#include "../../problems/problem5.h"

int main()
{
    string str = "abcdefghabcde";
    cout << "longest non overlapping repeated substring of string \"" << str << "\"" << " is: " << solve(str) << endl;

    str = "aabaabaaba";
    cout << "longest non overlapping repeated substring of string \"" << str << "\"" << " is: " << solve(str) << endl;

    return 0;
}