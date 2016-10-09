#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

int &get(int *a,int index)
{
    return a[index];
}

int main()
{
    int a[10];
    for (int i = 0;i != 10;++ i)
        get(a,i) = i;
    for (auto c : a)
        cout << c << endl;
    return 0;
}
