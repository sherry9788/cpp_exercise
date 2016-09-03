#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<string> svec;
    string s;
    while(cin>>s)
        svec.push_back(s);
    for(auto &s:svec)
        for(auto &a:s)
            a=toupper(a);
    for(auto s:svec)
        cout<<s<<endl;
}
