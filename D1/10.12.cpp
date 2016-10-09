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

bool com(sales s1,sales s2)
{
    return s1.isbn() > s2.isbn();
}

int main()
{
    vector<sales> sv;
    string s;
    while (cin >> s)
    {
        sales sa(s);
        sv.push_back(s);
    }
    sort(sv.begin(),sv.end(),com);
    for (auto c:sv)
        cout << c.isbn() << endl;
}
