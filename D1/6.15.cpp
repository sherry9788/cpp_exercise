#include <iostream>

using namespace std;

string::size_type find_char(string &s,char c,string::size_type &occurs)
{
    string::size_type send = s.size(),i = 0,myres = 0;
    for (occurs = 0;i != send;i ++)
    if (s[i] == c){
        if(occurs == 0)
            myres = i + 1;
            ++ occurs;
    }
    return myres ;
}

int main()
{
    string str;
    getline(cin,str);
    string::size_type occurs;
    auto ce = find_char(str,'a',occurs);
    cout << ce << endl << occurs << endl;
    return 0;
}
