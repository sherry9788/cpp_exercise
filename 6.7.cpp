#include <iostream>
#include <stdlib.h>

using namespace std;

int mycount()
{
    static int ti = 0;
    return ti ++;
}

int main()
{
    loop:
    system("pause");
    cout << mycount() << endl;
    goto loop;
    return 0;
}
