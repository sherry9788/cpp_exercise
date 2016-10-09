#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cassert>
#include <math.h>
#include <random>

using namespace std;

void output(int *a)
{
    for(int i = 0;i <= 9;++ i)
        cout << a[i] << " ";
    cout << endl;
}

void msort(int *a,int i)
{
    for (int m = 0;m < 10;++ m){
        int n = m,j = m,x;
        for (;n < 10;++ n){
            j = a[j] > a[n] ? j : n;
        }
        x = a[m];
        a[m] = a[j];
        a[j] = x;
    }
}

int main()
{
    int a[10], i;
    for (i = 0;i < 10;i ++)
        a[i] = rand();
    output(a);
    msort(a, 10);
    output(a);
    return 0;
}
