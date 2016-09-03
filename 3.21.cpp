#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<int> ivec(10,1);
    cout<<ivec.size()<<endl;
    auto iter=ivec.begin();
    while(iter!=ivec.end())
        cout<<*iter<<endl,iter++;
    return 0;
}
