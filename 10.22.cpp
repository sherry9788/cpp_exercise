#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

bool check(string s,int i)
{
    return s.size() >= i;
}

int main()
{
loop:
    vector<string> sv;
    string s;
    while(cin >> s)
        sv.push_back(s);
    cout << count_if(sv.begin(),sv.end(),bind(check,_1,5)) << endl;
    return 0;
}
