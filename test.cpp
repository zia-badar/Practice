#include <iostream>

using namespace std;

class class_
{
    public:
        int i;
        void (*func)(int);
        class_(){}
        class_(void (*f)(int)): func(&class_::member_func){}
        class_(int _): i(_) {}
        void member_func(int i){cout << i;}
};

int main()
{
    class_ obj1(1);
    class_ obj2(2);
    cout << obj1.i << " " << obj2.i << endl;
    obj2 = obj1;
    cout << obj1.i << " " << obj2.i << endl;
    return 0;
}
