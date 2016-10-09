#include <iostream>
using namespace std;

int main()
{
    int a=3,b=4;
//    decltype((a)) c;
//错误！a此时是一个表达式，是一个左值，所以c是一个引用。
    decltype(a=b) d=b;//d是一个引用
    return 0;
}
