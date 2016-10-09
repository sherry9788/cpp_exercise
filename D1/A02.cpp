#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

void born(int *rbt)
{
    int nr = 0;
    for (int j = 2;j <= 4;++ j)
    {
        nr += rbt[j];
    }
    rbt[4] = rbt[3];
    rbt[3] = rbt[2];
    rbt[2] = rbt[1];
    rbt[1] = rbt[0];
    rbt[0] = nr;
}

int main()
{
    int rbt[5]={1,0,0,0,0},days,i = 1;
    cin >> days;
    for (;i <= days;i ++)
        born(rbt);
    for (auto c:rbt)
        cout << c << " ";
    born(rbt);
    return 0;
}
