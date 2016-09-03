#include <iostream>

using namespace std;

void myswap(int *(&a),int *(&b))
{
    int *c;
    c = b;
    b = a;
    a = c;
}

int main()
{
    int a = 1,b = 2;
    int *c = &a,*d = &b;
    myswap(c,d);
    cout << *c << endl << *d <<endl;
    return 0;
}
