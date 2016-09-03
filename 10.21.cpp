#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int i = 100;
    auto f = [&] { if(i>=0) --i; };
    for ( int j = 1;j <= 100;++ j){
        f();
    }
    cout << i << endl;
    return 0;
}
