#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

char &get_value(string &s,string::size_type i)
{
    return s[i-1];
}

int main()
{
    string str;
    getline(cin,str);
    string::size_type i;
    cin >> i;
    system("pause");
    get_value(str,i) = '1';
    system("pause");
    cout << str << endl;
    return 0;
}
