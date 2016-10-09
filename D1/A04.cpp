#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

void fact(int n)
{
    int sum(0);
    for (int i = 1;i <= n/2;i ++)
        if (n % i == 0)
        sum += i;
    if (sum == n)
        cout << n << endl;
}

int main()
{
    int b;
    cin >> b;
    for (int n = 1;n <= b;++ n)
        fact(n);
    return 0;
}
