#include <iostream>
#include <string>

using namespace std;
/*
int main()
{
    string s,line;
    while(cin>>s)
        line+=s;
    cout<<line<<endl;
    return 0;
}
*/

int main()
{
    string s,line;
    while(cin>>s)
        line=line+s+" ";
    cout<<line<<endl;
    return 0;
}
