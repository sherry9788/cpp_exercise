#include <iostream>
#include <string>

using namespace std;

string pre_suffix(const string& name, const string& pre,
                       const string& su)
{
    string ret(name);
    ret.insert(0, pre);
    ret.insert(ret.size(), su);

    return ret;
}

int main()
{
    string name("alan");
    cout << pre_suffix(name, "Mr.", ",Jr.");

    return 0;
}
