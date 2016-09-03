#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    map<int, int> m;
    m[0] = 1;

    for (const auto& e : m) cout << e.first << " " << e.second << "\n";

    vector<int> v;
    v[0] = 1;

    for (const auto& e : v) cout << e << "\n";

    map<int, string> map = {{1, "ss"}, {2, "sz"}};

    std::map<int, string>::key_type type_to_subscript = 1;

    std::map<int, string>::mapped_type type_to_return =
        map[type_to_subscript];

    return 0;
}
