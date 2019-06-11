#include "../../problems/problem2.h"

using namespace std;

int main()
{
    palaindrom_partitioning pp;
    cout << pp.solve("abcdeedcba") << endl;
    cout << pp.solve("abccbadeffed") << endl;
    cout << pp.solve("ababbbabbababa") << endl;
    return 0;
}
