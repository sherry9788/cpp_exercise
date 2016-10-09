#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

int main()
{
    list<string> l{"1","1231231","a","a"};
    cout << count(l.cbegin(),l.cend(),"a") << endl;
    return 0;
}
