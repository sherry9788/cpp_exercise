#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cassert>
#include <math.h>

using namespace std;

double f1(int i1,int i2,double r)
{
    return (-i2 + sqrt (r)) / (2 * i1);
}

double f2(int i1,int i2,double r)
{
    return (-i2 - sqrt (r)) / (2 * i1);
}

int main()
{
    cout << "Input a,b,c" << endl;
    int a, b, c;
    cin >> a >> b >> c;
    double r = b* b - 4 * a * c;
    if (r >= 0){
        cout << f1(a, b, r) << endl;
        cout << f2(a, b, r) << endl;
    }
    else
        cout << "No root" << endl;
    return 0;
}
