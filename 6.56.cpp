#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cassert>

using namespace std;

int f1(int, int);
int f2(int, int);
int f3(int, int);
int f4(int, int);

int main()
{
    vector<int(*) (int, int)> fvec;
    fvec.push_back(f1);
    fvec.push_back(f2);
    fvec.push_back(f3);
    fvec.push_back(f4);
    int a, b, c;
    cin >> a >> b >> c;
    auto fx = fvec[a];
    cout << fx(b, c) << endl;
    return 0;
}

int f1(int i1, int i2)
{
    return i1 + i2;
}

int f2(int i1, int i2)
{
    return i1 - i2;
}

int f3(int i1, int i2)
{
    return i1 * i2;
}

int f4(int i1, int i2)
{
    return i1 / i2;
}
