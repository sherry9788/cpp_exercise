#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    int a[10]={1,2,3,4,5,6,7,8,9,0};
    int *p=a,*pend=end(a);
    for(;p<pend;++p)
        *p=0;
    system("pause");
    for(p=begin(a);p<pend;++p)
        cout<<*p<<endl;
    return 0;
}
