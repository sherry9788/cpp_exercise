#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;

void output(int *d,int n1)
{
    for (int i = 0;i < n1;++ i)
        cout << d[i] << " ";
    cout << '\b' << endl;
}

void fx(int *b,int n,int k,int *d,int n1)
{
    int a[n-1];
    int i = 0;
    for(int index = 0;index < n;++ index)
    {
        if (b[index] != k)
            a[i ++] = b[index];
    }
    if (n != 1)
        for (int index = 0;index < n-1;++ index)
        {
            int j = a[index];
            d[n1-n+1] = j;
            fx(a,n - 1,j,d,n1);
        }
    else
        output (d,n1);
}

int main()
{
    int n;
    cin >> n;
    int n1 = n;
    int c[n];
    int d[n];
    for (int i = 0;i < n;++ i)
        c[i] = i + 1;
    for (int i = 1;i <= n1;++ i)
    {
        d[0] = i;
        fx(c,n,i,d,n1);
    }
    return 0;
}
