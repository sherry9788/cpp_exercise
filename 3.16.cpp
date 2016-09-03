#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<int> ivec;
    int i;
    while(cin>>i)
        ivec.push_back(i);
    cout<<ivec.size()<<endl;
    for(auto a:ivec)
        cout<<a;
    cout<<endl;
}
