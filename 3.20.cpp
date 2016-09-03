#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
int main()
{
    vector<int> ivec;
    int i;
    while(cin>>i)
        ivec.push_back(i);
    for(decltype(ivec.size()) n=0;n<=ivec.size()-2;n++)
        cout<<ivec[n]+ivec[n+1]<<endl;
}
*/

int main()
{
    vector<int> ivec;
    int i;
    while(cin>>i)
        ivec.push_back(i);
    for(decltype(ivec.size()) n=0;n<=ivec.size()-2;n++)
        cout<<ivec[n]+ivec[ivec.size()-n-1]<<endl;
}
