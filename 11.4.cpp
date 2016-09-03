#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main()
{
    map<string, size_t> wc;
    string cs;
    while (cin >> cs){
        for (auto &c:cs)
            c = toupper(c);
        ++ wc[cs];
    }
    for (auto c : wc)
        cout << c.first << " " << c.second << endl;
    return 0;
}
