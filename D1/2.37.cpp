#include <iostream>
using namespace std;

int main()
{
    int a=3,b=4;
//    decltype((a)) c;
//����a��ʱ��һ�����ʽ����һ����ֵ������c��һ�����á�
    decltype(a=b) d=b;//d��һ������
    return 0;
}
