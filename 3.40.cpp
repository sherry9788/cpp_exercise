#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    char a[100]="Fuck",b[100]=" You!",c[1000];
    strcat(a,b);
    cout<<a<<endl;
    strcpy(b,a);
    cout<<b<<endl;
}
