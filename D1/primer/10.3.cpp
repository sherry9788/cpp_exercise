#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

int main()
{
    vector<int> ivec{1,2,3,4,5,6,6};
    cout << accumulate(ivec.cbegin(),ivec.cend(),0) << endl;
    return 0;
}
