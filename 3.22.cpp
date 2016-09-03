#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<string> text;
    string s;
    while(getline(cin,s))
        text.push_back(s);
    auto &a=text[0];
    for(auto &b:a)
        b=toupper(b);
    for(auto c:text)
        cout<<c<<endl;
    return 0;
}
