#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    vector<int> ivec(10,1);
    int arr[24]={},i=0;
    auto pend=ivec.end();
    for(auto iter=ivec.begin();iter<pend;iter++)
        arr[i]=*iter,i++;
    for(auto c:arr)
        cout<<c<<endl;
    return 0;
}
