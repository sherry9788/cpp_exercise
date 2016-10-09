#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

int main()
{
    list<const char*> l{"Mooophy", "pezy", "Queeuqueg"};
    vector<string> v;
    v.assign(l.cbegin(), l.cend());
    for (const auto& ch : v)
        cout << ch << endl;
    return 0;
}
