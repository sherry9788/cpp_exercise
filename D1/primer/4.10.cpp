#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    vector<int> ivec;
    int ip;
    while(cin>>ip && ip!=42)
        ivec.push_back(ip);
    for(auto c:ivec)
        cout<<c<<endl;
    return  0;
}
