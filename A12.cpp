#include <iostream>
#include <string>

using namespace std;

void del(int *a,int *b,int n)
{
    int j = 0;
    for (int i = 0;i < n;++ i)
        if(i % 3 != 0){
            b[j] = a[i];
            ++ j;
        }
}

void myswap(int *a,int *b,int n)
{
    for (int i = 0;i < n;++ i)
        a[i] = b[i];
}

int main()
{
    int n;
    cin >> n;
    int a[n],b[n];
    for (int i = 0;i < n;++ i)
        a[i] = i+1;
    while (n != 1){
        del (a,b,n);
        n = n - (n+2)/3;
        myswap(a,b,n);
    }
    cout << a[0] << endl;
    return 0;
}
