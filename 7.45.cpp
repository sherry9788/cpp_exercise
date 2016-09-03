#include <iostream>
#include <vector>

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
//    vector<C> vec(10);
    return 0;
}
