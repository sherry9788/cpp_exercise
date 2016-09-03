#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

int main()
{
    int x[10] ;
    int *p = x ;
    system("pause");
    cout << sizeof(x)/sizeof(*x) << endl;
    system("pause");
    cout << sizeof(p)/sizeof(*p) << endl;
    return 0;
}
