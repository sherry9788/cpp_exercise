#include <iostream>
using namespace std;

int main()
{
    const int i=1024;
    const int &r1=i;
//    int &r2=i;
//错误！试图让一个非常量引用指向一个常量对象。
    int j=1024;
    const int &k=j;
//    k++;
//错误！试图自增一个常量引用。
    const int &l=42;
    const int &l1=j*2;
//    int &l2=j*2;
//错误！试图让一个非常量引用绑定到常量上。
    double m=3.14;
    const int &l3=m;
/*
    类似于
    const int &l4=1024
    等价于
    const int temp=1024;
    const int &l4=int;
    故这种行为是合法的，同时如果是非常量引用，这样的行为就是不合法的。
    */
    int mi=-1;
//    int &mr=0;
    int *const p2=&mi;
    const int mi1=-1,&r=0;
    const int *const p3=&mi;
//    const int *const p3;
//常量必须初始化。
    const int mi2=i;
    const int &mr2=i;
    mr2++;
    return 0;
}
