#include <iostream>
using namespace std;

int main()
{
    int i=42,*p=&i,&r=i;
//    decltype(r) r1;
//����r��һ�����á�
    decltype(r+0) m;
//r+0���صĽ����int��
//    decltype(*p) r3;
//����*p���صĽ����һ�����á�
//    decltype((i)) r4;
//����(i)���ص�ֵ��һ�����á�
    int a=4,b=4;
    decltype(a) c=a;//c��int
    decltype((b)) d=b;//d��һ��int&
    ++c;
    ++d;
    cout<<a<<"\n"<<b<<endl;
    return 0;
}
