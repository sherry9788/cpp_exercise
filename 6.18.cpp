#include <iostream>
#include <cstdlib>

using namespace std;

using matrix = int[5];

bool compare(matrix *p1,matrix *p2,size_t i1,size_t i2)
{
    for(size_t j1 = 0,j2;j1 != i1;p1 ++,p2 ++,j1 ++){
        j2 = 0;
        for(int *p11 = *p1,*p22 = *p2;j2 != i2;p11 ++,p22 ++,j2 ++)
        if (*p11 != *p22)
        return 0;
    }
    return 1;
}

int main()
{
    loop:
        int a[5][5] = {{0,0,0,0,0},{},{},{},{}},b[5][5] = {{},{},{},{},{0,0}};
    system("pause");
    cout << compare(a,b,5,5) << endl;
    goto loop;
    return 0;
}
