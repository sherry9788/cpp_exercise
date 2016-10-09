#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

/*
constexpr bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}
*/

int main()
{
    string s1,s2;
    cout << "Input s1:" << endl;
    getline(cin,s1);
    cin.clear();
    cout << "Input s2:" << endl;
    getline(cin,s2);
    cout << isShorter(s1,s2);
    return 0;
}
