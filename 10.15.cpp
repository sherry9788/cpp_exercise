#include <iostream>

using namespace std;

int main()
{
    int i = 42;
    auto add = [i](int num){return i + num;};
    return 0;
}
