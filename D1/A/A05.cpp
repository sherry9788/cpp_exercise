#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

int factorial(int n)
{
    if (n != 1)
        return factorial(n - 1) * n;
    return 1;
}

int main()
{
    int sum = 0;
    for (int i = 1;i <= 20;++ i)
        sum += factorial(i);
    cout << sum << endl;
    return 0;
}
