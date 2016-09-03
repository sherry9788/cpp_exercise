#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

int main()
{
    cout<<"Input 10 numbers."<<endl;
    vector<int> ivec;
    int num;
    while(cin>>num)
        ivec.push_back(num);
    system("pause");
    auto beg=ivec.begin(),en=ivec.end()-1;
    for(;beg<en;beg++,en--)
        cout<<*beg+*en<<endl;
    return 0;
}
