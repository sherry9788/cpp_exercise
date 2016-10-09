#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

void printvec(vector<int> ivec,int sz)
{
    if (sz > 1)
        printvec(ivec,sz - 1),
        cout << ivec[sz - 1];
    else cout  << ivec[0];
}

int main()
{
    int i;
    vector<int> ivec;
    while (cin >> i)
        ivec.push_back(i);
    printvec(ivec,ivec.size());
    return 0;
}
