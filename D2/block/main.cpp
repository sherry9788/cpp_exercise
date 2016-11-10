#include "array.h"

#include <sstream>
#include <vector>
#include <algorithm>

// test function
void test();

int main()
{
    test();
    return 0;
}

void test()
{
    std::cout << "please input the data" << std::endl;
    std::istream_iterator<double> beg(std::cin);
    std::istream_iterator<double> end;
    Array<double> myArray(beg, end);

    std::cout << "push_back test" << std::endl;

    for(int i = 1; i < 100; ++i)
    {
        myArray.push_back(i / 10.);
    }

    myArray.print_all(WITH_DATA);

    std::cout << "push_front test" << std::endl;

    for(int i = 1; i < 100; ++i)
    {
        myArray.push_back(i / 10.);
    }

    myArray.print_all(WITH_DATA);
    
    std::cout << "insert test" << std::endl;

    myArray.insert(1, 1.024);

    myArray.print_all(WITH_DATA);

    std::cout << "for_each test" << std::endl;

    std::for_each(myArray.begin(), myArray.end(), [](double &d) {d /= 2;});

    myArray.print_all(WITH_DATA);

    std::cout << "count_if test" << std::endl;
    
    std::cout << std::count_if(myArray.rbegin(), myArray.rend(),
            [](double d){return d > 2;}) << std::endl;
}
