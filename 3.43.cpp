#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    int arr[3][4]={{1,2,3,4},{},{}};
    for(int (&c)[4]:arr){
        for(int d:c)
            cout<<d<<" ";
        cout<<endl;
    }
    system("pause");
    for(int i=0;i<=2;i++){
        for(int j=0;j<=3;j++)
            cout<<arr[i][j]<<" ";
        cout<<endl;
    }
    system("pause");
    int (*pend1)[4]=end(arr);
    for(int (*p1)[4]=arr;p1<pend1;p1++){
        int *pend2=&(*p1)[3];
        for(int *p2=*p1;p2<=pend2;p2++)
            cout<<*p2<<" ";
        cout<<endl;
    }
    return 0;
}
