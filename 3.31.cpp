#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    int a[10]={};
    for(int i=0;i<sizeof(a);i++)
        a[i]=i;
    int *pend=end(a);
    for(int *p=a;p<pend;p++)
        cout<<*p<<endl,system("pause");
    return 0;
}
