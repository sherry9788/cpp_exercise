#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

int main()
{
    vector<int> ivec(10,1);
    for(auto &iter:ivec)
        iter=2*iter;
    for(auto c:ivec)
        cout<<c<<endl;
    return 0;
}
