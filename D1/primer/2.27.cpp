#include <iostream>
using namespace std;

int main()
{
    const int i=1024;
    const int &r1=i;
//    int &r2=i;
//������ͼ��һ���ǳ�������ָ��һ����������
    int j=1024;
    const int &k=j;
//    k++;
//������ͼ����һ���������á�
    const int &l=42;
    const int &l1=j*2;
//    int &l2=j*2;
//������ͼ��һ���ǳ������ð󶨵������ϡ�
    double m=3.14;
    const int &l3=m;
/*
    ������
    const int &l4=1024
    �ȼ���
    const int temp=1024;
    const int &l4=int;
    ��������Ϊ�ǺϷ��ģ�ͬʱ����Ƿǳ������ã���������Ϊ���ǲ��Ϸ��ġ�
    */
    int mi=-1;
//    int &mr=0;
    int *const p2=&mi;
    const int mi1=-1,&r=0;
    const int *const p3=&mi;
//    const int *const p3;
//���������ʼ����
    const int mi2=i;
    const int &mr2=i;
    mr2++;
    return 0;
}
