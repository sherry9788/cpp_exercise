#include <iostream>
#include <string>
#include <list>

using namespace std;

int main()
{
    list<string> input;
    for (string str; cin >> str; input.push_back(str))
        ;
    for (auto iter = input.begin(); iter != input.end(); ++iter)
        cout << *iter << endl;

    return 0;
}
