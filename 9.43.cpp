#include <string>
#include <iostream>

using namespace std;

void Replace(string& s, const string& oldVal, const string& newVal)
{
    for (auto beg = s.begin(); beg != s.end(); ++beg) {
        if (*beg != oldVal.front()) continue;
        if (distance(beg, s.end()) <
            distance(oldVal.begin(), oldVal.end()))
            break;
        if (string{beg, beg + oldVal.size()} == oldVal) {
            auto pos = distance(s.begin(), beg);
            s.erase(beg, beg + oldVal.size());
            s.insert(beg, newVal.cbegin(), newVal.cend());
            beg = next(s.begin(), pos + newVal.size() - 1);
        }
    }
}

int main()
{
    {
        string str{"To drive straight thru is a foolish, tho courageous act."};
        Replace(str, "thru", "through");
        Replace(str, "tho", "though");
        cout << str << endl;
    }
    {
        string str{
            "To drive straight thruthru is a foolish, thotho courageous act."};
        Replace(str, "thru", "through");
        Replace(str, "tho", "though");
        cout << str << endl;
    }
    {
        string str{"To drive straight thru is a foolish, tho courageous act."};
        Replace(str, "thru", "thruthru");
        Replace(str, "tho", "though");
        cout << str << endl;
    }
    {
        string str{"my world is a big world"};
        Replace(str, "world",
                "worldddddddddddddddddddddddddddddddddddddddddddddddd");
        cout << str << endl;
    }
    return 0;
}
