#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isshorter(const int i,const int j)
{
    return i/10 > j/10;
}

int main()
{
    vector<int> ivec;
    int i;
    while(cin >> i)
        ivec.push_back(i);
    sort(ivec.begin(),ivec.end());
    auto eu = unique(ivec.begin(),ivec.end());
    ivec.erase(eu,ivec.end());
    stable_sort(ivec.begin(),ivec.end(),isshorter);
    for (auto c:ivec)
        cout << c << endl;
    return 0;
}
