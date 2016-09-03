#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

int main()
{
    vector<int> ivec(5,1);
    list<int> ilst(5,1);
    bool b = (vector<int> (ilst.begin(),ilst.end())) == ivec;
    cout << b << endl;
    return 0;
}
