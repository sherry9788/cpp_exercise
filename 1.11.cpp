#include <iostream>
using namespace std;

int main()
{
    int a,b,c,d;
    cin>>a>>b;
    d=a>b? a:b;
    c=a>b? b:a;
    while (c<=d){
        cout<<c<<" ";
        c++;
    }
    cout<<endl;
    return 0;
}
