#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    int a[10]={},b[10];
    for(int i=0;i<sizeof(a);i++)
        a[i]=i;
    int *pend=end(a);
    for(int *p=a;p<pend;p++)
        b[*p]=*p;
    int *pend1=end(b);
    for(int *p=b;p<pend1;p++)
        cout<<*p<<endl;
    return 0;
}
