#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool com(string s)
{
    return s.size() < 5;
}

int main()
{
    vector<string> sv;
    string s;
    while (cin >> s)
        sv.push_back(s);
    auto ne = partition(sv.begin(),sv.end(),com);
    for_each(ne,sv.end(),[] (string &s) {cout << s << endl;});
    return 0;
}
