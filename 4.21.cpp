#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

int main()
{
    vector<int> ivec;
    cout<<"Input some numbers."<<endl;
    int inp;
    while (cin>>inp)
        ivec.push_back(inp);
    for(auto &c:ivec)
        c = ( ( c % 2 == 1 ) ? c*2 : c ) ;
    for(auto c:ivec)
        cout<<c<<" "<<endl;
    return 0;
}
