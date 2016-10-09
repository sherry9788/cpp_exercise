#include <iostream>
using namespace std;

int main()
{
    const int v2=0;//top
    int v1=v2;
    int *p1=&v1,&r1=v1;
    const int *p2=&v2;//low

    return 0;
}
