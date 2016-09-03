#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

int main()
{
    vector<int> ivec1(5,1),ivec2(5,1);
    bool b = ivec1 == ivec2;
    cout << b << endl;
    return 0;
}
