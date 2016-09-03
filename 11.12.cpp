#include <vector>
#include <utility>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    vector<pair<string, int>> vec;
    string str;
    int i;
    while (cin >> str >> i)
        vec.push_back(pair<string, int>(str, i));

    for (const auto& p : vec)
        cout << p.first << ":" << p.second << endl;
}
