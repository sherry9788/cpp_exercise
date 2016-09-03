#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    int arr[]={1,1,1,3,4,5,6};
    vector<int> ivec(begin(arr),end(arr));
    for(auto c:ivec)
        cout<<c<<endl;
    return 0;
}
