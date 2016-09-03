#include <iostream>
#include <stdlib.h>
#include "6.8.h"

using namespace std;

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

int myabs(int fi)
{
    return fi > 0 ? fi : -fi;
}
