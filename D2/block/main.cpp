#include "block.h"
#include <sstream>

int main()
{
    Array<int> x((std::istream_iterator<int>(std::cin)), (std::istream_iterator<int>()));
    x.print_all(1);

    for(auto iter = x.rbegin(); iter!= x.rend(); ++iter)
    {
        std::cout << *iter << std::endl;
    }
    return 0;
}
