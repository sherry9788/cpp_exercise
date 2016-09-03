#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct sales
{
    string no;
    string isbn()
    {
        return no;
    }
    sales(string s):
        no(s) {}
};

int main()
{
    vector<sales> sv;
    string s;
    while (cin >> s)
    {
        sales sa(s);
        sv.push_back(s);
    }
    sort(sv.begin(),sv.end(),[] (sales s1,sales s2){return s1.isbn() >= s2.isbn();});
    for (auto c:sv)
        cout << c.isbn() << endl;
}
