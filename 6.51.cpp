#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cassert>

using namespace std;

void f(int i1,int i2)
{
    cout << "int" << endl;
}

void f(double d1,double d2 = 3.14)
{
    cout << "double" << endl;
}

int main()
{
//    f(2.56, 42):
    f(42);
    f(42, 0);
    f(2.56, 3.14);
    return 0;
}
