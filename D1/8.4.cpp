#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("sherry.txt");
    vector<string> sv;
    string s;
    while (getline(in,s))
        sv.push_back(s);
    for (auto c:sv)
        cout << c << endl;
    return 0;
}
