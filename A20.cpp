#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

double dis()
{
    double a1 = 0,a2 = 0;
    a1 = rand()%1000;
    a2 = rand()%1000;
    double b1 = a1 / 1000,b2 = a2 / 1000;
    return (b1 > b2) ? (b1 - b2) : (b2 - b1);
}

int main()
{
    int n;
    cin >> n;
    double sum = 0,temp;
    for (int i = 0;i < n;++ i)
        temp = dis(),sum += temp;
    sum /= n;
    cout << sum << endl;
    return 0;
}
