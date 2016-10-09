#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

inline double dis()
{
    double a1 = 0,a2 = 0;
    a1 = rand()%1000;
    a2 = rand()%1000;
    double b1 = a1 / 1000,b2 = a2 / 1000;
    return sqrt(b1*b1 + b2*b2);

}

int main()
{
    int n;
    for (n = 1;n <= 100000;n += 1000){
    double sum = 0,temp;
    for (int i = 0;i < n;++ i)
        if (dis() <= 1.0)
        ++ sum;
    sum /= n;
    cout << sum * 4 << endl;
    }
    return 0;
}
