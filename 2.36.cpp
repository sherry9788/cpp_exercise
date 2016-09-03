#include <iostream>
using namespace std;

int main()
{
    int i=42,*p=&i,&r=i;
//    decltype(r) r1;
//错误！r是一个引用。
    decltype(r+0) m;
//r+0返回的结果是int。
//    decltype(*p) r3;
//错误！*p返回的结果是一个引用。
//    decltype((i)) r4;
//错误！(i)返回的值是一个引用。
    int a=4,b=4;
    decltype(a) c=a;//c是int
    decltype((b)) d=b;//d是一个int&
    ++c;
    ++d;
    cout<<a<<"\n"<<b<<endl;
    return 0;
}
