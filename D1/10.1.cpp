#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

int main()
{
    vector<int> v{11,1,1,1,1,111,11,111,1};
    cout << count(v.cbegin(),v.cend(),1) << endl;
    return 0;
}
