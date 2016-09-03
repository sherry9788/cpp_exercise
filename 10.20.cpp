#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> ivec{1,2,3,4,1,2,3,2,2,2,2,2};
    cout << count_if(ivec.begin(),ivec.end(),[] (int i) { return i < 2;}) << endl;
    return 0;
}
