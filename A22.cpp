#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

int main()
{
    int n,s = 0;
    cin >> n;
    for (int i = 0;i < n;i ++)
        for (int j = 0,c = 100;j < 100;++ j){
            if(c)
                if(rand()%2){
                    s += 20;
                    c -= 20;
                }
                else{
                    s -= 20;
                    c += 20;
                }
        }
    cout << s << endl;
    return 0;
}
