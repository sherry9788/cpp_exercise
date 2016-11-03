#include "block.h"
#include <sstream>

int main()
{
    Array<int> x;
    for(int i = 0; i < 110; ++i)
        x.push_back(i);
    x.print_all(1);
    x.insert(98, 1024);
    x.print_all(1);
    x.compress();
    x.print_all(1);
    return 0;
}
