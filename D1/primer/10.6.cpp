#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> ivec{1,2,3,4,5};
    fill_n(ivec.begin(),ivec.size(),0);
    for (auto c:ivec)
        cout << c << endl;
    return 0;
}
