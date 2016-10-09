#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

void myadd (const double *c1,const double *c2,double *c)
{
    c[0] = c1[0] + c2[0];
    c[1] = c1[1] + c2[1];
}

void myminus (const double *c1,const double *c2,double *c)
{
    c[0] = c1[0] - c2[0];
    c[1] = c1[1] - c2[1];
}

void mymutiply (const double *c1,const double *c2,double *c)
{
    c[0] = c1[0] * c2[0] - c1[1] * c2[1];
    c[1] = c1[0] * c2[1] + c1[1] * c2[0];
}

void mydivide (const double *c1,const double *c2,double *c)
{
    c[0] = (c1[0] * c2[0] + c1[1] * c2[1]) / (c2[0] * c2[0] + c2[1] * c2[1]);
    c[1] = (c1[1] * c2[0] - c1[0] * c2[1]) / (c2[0] * c2[0] + c2[1] * c2[1]);
}

void output (const double *c)
{
    cout << c[0] << " + " << c[1] << "i" << endl;
}

int main()
{
    loop:
    double c1[2],c2[2],c[2];
    cout << "Input c1:" << endl;
    cin >> c1[0] >> c1[1];
    cout << "Input c2:" << endl;
    cin >> c2[0] >> c2[1];
    myadd(c1,c2,c);
    output(c);
    myminus(c1,c2,c);
    output(c);
    mymutiply(c1,c2,c);
    output(c);
    mydivide(c1,c2,c);
    output(c);
    goto loop;
    return 0;
}
