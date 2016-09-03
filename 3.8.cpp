#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s("1234567");
//    decltype(s.size()) i=0;
//    while (i<=s.size())
//        s[i]='X',i++;
    for(decltype(s.size()) i=0;i<=s.size();i++)
        s[i]='X';
    cout<<s<<endl;
    return 0;
}
