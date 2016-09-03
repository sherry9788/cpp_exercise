#include <iostream>
#include <stdlib.h>

using namespace std;

int myabs(int fi)
{
    return fi > 0 ? fi : -fi;
}

int main()
{
    loop:
    int i;
    cout << "Input a number:" << endl;
    cin >> i;
    cout << myabs(i) << endl;
    goto loop;
    return 0;
}
