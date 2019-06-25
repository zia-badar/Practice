#include "../../problems/problem6.h"


int main()
{
    string str = "abc";
    cout << "longest repeated subsequence of string \"" << str << "\"" << " is: " << solve(str) << endl;
    str = "aab";
    cout << "longest repeated subsequence of string \"" << str << "\"" << " is: " << solve(str) << endl;
    str = "axxxy";
    cout << "longest repeated subsequence of string \"" << str << "\"" << " is: " << solve(str) << endl;

    return 0;
}