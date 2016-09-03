#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<vector<int>> ivec;
//    vector<string> svec=ivec;
//类型不同，不能作为副本。
    vector<string> svec1(10,"null");
    return 0;
}
