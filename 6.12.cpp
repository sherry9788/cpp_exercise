#include <iostream>

using namespace std;

void myswap(int &i,int &j)
{
    int m;
    m = i;
    i = j;
    j = m;
}

int main()
{
    loop:
    int i1,i2;
    cin >> i1 >> i2;
    myswap(i1,i2);
    cout << i1 << endl << i2 << endl;
    goto loop;
    return 0;
}
