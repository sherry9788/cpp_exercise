#include <iostream>
#include <string>
using namespace std;
/*
int main()
{
    string s1,s2;
    cout<<"Input s1"<<endl;
    getline(cin,s1);
    cout<<"Input s2"<<endl;
    getline(cin,s2);
    cout<<"Result:"<<endl;
    if (s1==s2)
        cout<<s1;
    else
        s1>s2? cout<<s1:cout<<s2;
    cout<<endl;
    return 0;
}
*/

int main()
{
        string s1,s2;
    cout<<"Input s1"<<endl;
    getline(cin,s1);
    cout<<"Input s2"<<endl;
    getline(cin,s2);
    cout<<"Result:"<<endl;
    if (s1.size()==s2.size())
        cout<<"Equal";
    else
        s1.size()>s2.size()? cout<<s1:cout<<s2;
    cout<<endl;
    return 0;
}
