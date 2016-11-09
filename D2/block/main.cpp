#include "block.h"

#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
    Array<int> a;
    for(int i = 10; i >= 0; --i)
        a.push_back(i);

    std::sort(a.begin(), a.end());
    // std::sort(a.rbegin(), a.rend()); // 宝贝我咋通不过这个, 用begin和end就能通过

    a.print_all(1);
    return 0;
}
