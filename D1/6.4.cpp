#include <iostream>
#include <stdlib.h>

using namespace std;

int myfact(int fi)
{
    int result = 1;
    for (;fi != 1;fi --)
        result *= fi;
    return result;
}

int main()
{
    loop:
    int i;
    cout << "Input a number:" << endl;
    cin >> i;
    cout << myfact(i) << endl;
    goto loop;
    return 0;
}
