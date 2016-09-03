#include <iostream>

using namespace std;

struct frac
{
    int u;
    int d;
    void print()
    {
        if (d == 1)
            cout << u << endl;
        else
            cout << u << "/" << d << endl;
    }
    frac(int u1,int d1):
        u(u1),d(d1) {};
};

void yf(frac &f1)
{
    int i = f1.u > f1.d ? f1.d : f1.u;
    for (;i > 0;-- i)
        if (f1.u % i == 0 && f1.d % i ==0)
        break;
    f1.u /= i;
    f1.d /= i;
}

void add(frac f1,frac f2)
{
    frac f3(f1.u*f2.d + f1.d*f2.u,f1.d * f2.d);
    yf (f3);
    f3.print();
}

void muti(frac f1,frac f2)
{
    frac f3(f1.u * f2.u,f1.d * f2.d);
    yf (f3);
    f3.print();
}

void add(frac f1,int i2)
{
    frac f3(f1.u + f1.d * i2,f1.d);
    yf(f3);
    f3.print();
}

void muti(frac f1,int i2)
{
    frac f3(f1.u * i2,f1.d);
    yf (f3);
    f3.print();
}

int main()
{
    frac f1(5,3),f2(7,10),f3(3,7),f5(1,6),f6(1,9);
    int i4(14);
    muti(f1,f2);
    muti(f3,i4);
    add(f5,f6);
    return 0;
}
