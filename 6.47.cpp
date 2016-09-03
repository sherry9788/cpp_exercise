#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cassert>

using namespace std;

void printvec(vector<int> ivec,int sz)
{
    assert(ivec.size() <= 5);
    if (sz > 1)
        printvec(ivec,sz - 1),
        cout << ivec[sz - 1] << endl;
    else cout  << ivec[0] << endl;
}

int main()
{
    int i;
    vector<int> ivec;
    while (cin >> i)
        ivec.push_back(i);
    printvec(ivec,ivec.size());
    cout << "The length of the vector is: " << ivec.size() << endl;
    return 0;
}
