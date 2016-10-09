#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    const char ca[]="hello";
//    const char ca[]={'h','e','l','l','o'};
    const char *cp=ca;
    while(*cp)
        cout<<*cp<<endl,cp++;
    return 0;
}
