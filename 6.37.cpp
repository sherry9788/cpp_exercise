#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

/*
using ce = string [10];

ce &get_string(string);
*/

auto get_string(string) -> string(&)[10];

int main()
{
    string s;
    cin >> s;
    auto *p = get_string(s);
    cout << *p;
    return 0;
}

string (&get_string(string s))[10]
{
    static string str[10];
    for(int i =0;i != 10;++ i)
    str[i] = s;
    return str;
}
