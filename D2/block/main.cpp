#include "block.h"
#include <sstream>
#include <vector>

int main()
{
    std::ostream_iterator<int> out(std::cout, "\n");
    Array<int> a(20, 20);
    for(int i = 10; i < 40; ++i)
        a.push_back(i);
    for(int i = 9; i > -1; --i)
        a.push_front(i);
    a.print_all();
    std::cout << "------------------------------" << std::endl;
    for(auto c = a.rbegin(); c != a.rend(); ++c)
    {
        *out = *c;
    }
    return 0;
}
