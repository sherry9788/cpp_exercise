#include <iostream>

using namespace std;

int myadd(initializer_list<int> mi)
{
    int sum = 0;
    for (auto beg = mi.begin();beg != mi.end();++ beg)
        sum += *beg;
    return sum;
}

int main()
{
    initializer_list<int> ce = {1,2,3,4,5,6};
    cout << myadd(ce) << endl;
    return 0;
}
