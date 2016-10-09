#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool dec(int n)
{
    for (int i = 1;i != 100000;++ i)
        if (n+100 == i*i)
            for (int j = 1;j != 100000;++ j)
                if (n+268 == j*j)
                    return 1;
    return 0;
}

int main()
{
    int n,a[100] = {},k = 0;
    for (n = 1;n <= 100000;++ n)
        if (dec(n))
        a[k ++] = n;
    for (auto c:a){
        if (c != 0)
        cout << c << endl;
    }
    return 0;
}
