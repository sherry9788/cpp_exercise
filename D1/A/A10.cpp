#include <iostream>
#include <random>

using namespace std;

int cub(int i)
{
    return i*i*i;
}

int fx(int i,int n)
{
    int res = 0;
    for (int j = 1;j <= n;++ j){
        res += i;
        i += 2;
    }
    return res;
}

int main()
{
    cout << "Input a number:" << endl;
    int n,i;
    cin >> n;
    for (i = 1;;i += 2){
        if (fx(i,n) == cub(n))
            break;
    }
    cout << n << "^3 = ";
    for (int j = 1;j <= n;++ j){
        cout << i;
        if (j != n)
            cout << " + ";
        i += 2;
    }
    cout << '\b' << endl;
    cout << endl;
    return 0;
}
