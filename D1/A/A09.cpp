#include <iostream>
#include <random>

using namespace std;

int main()
{
    int a[20];
    for (int i = 0;i < 20;++ i)
        a[i] = rand()%100;
    for (auto c:a)
        cout << c << " ";
    cout << endl;
    int j1(0),j2(100),j3(0);
    for (int i = 0;i < 20;++ i)
        j1 = j1>a[i] ? j1:a[i];
    cout << j1 << endl;
    for (int i = 0;i < 20;++ i)
        j2 = j2<a[i] ? j2:a[i];
    cout << j2 << endl;
    for (int i = 0;i < 20;++ i)
        j3 += a[i];
    cout << j3 << endl;
    cout << (double)j3/20 << endl;
    return 0;
}
