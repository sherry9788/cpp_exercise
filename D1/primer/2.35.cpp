#include <iostream>
using namespace std;

using namespace std;
int main()
{
    const int i=42;
    auto j=i;
    j++;
    cout<<j<<endl;
    const auto m=i;
//    m++;
    cout<<m<<endl;
//    auto &k=1;
    const auto k=1;
    auto *p=&i;
    *p++;//p�Ƕ����ͳ��������ã����Ƕ������ʱ���������ᱨ��
    const auto q=i,&k2=i;
//    q++;
    cout<<k2<<endl;
    cout<<*p<<endl;
}
