#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

string (&get_string(string s))[10]
{
    static string str[10];
    for(int i =0;i != 10;++ i)
    str[i] = s;
    return str;
}

int main()
{
    string s;
    cin >> s;
    auto *p = get_string(s);
    cout << *p;
    return 0;
}
