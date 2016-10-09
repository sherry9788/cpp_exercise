#include <iostream>

using namespace std;

class NoDefault
{
    int i;
    int j;
    int &k;
    NoDefault(int p):i(0),k(p) {};
};

class C
{
    NoDefault m;
};

int main()
{
    return 0;
}
