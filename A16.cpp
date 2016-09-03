#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n,j(1);
    cin >> n;
    int m = n;
    while (n/10 != 0){
        n /= 10;
        j ++;
    }
    char s[j+1];
    for (int i = 1;i <= j;++ i){
        s[j-i] = (char)(m % 10 + 48);
        m /= 10;
    }
    for (auto c:s)
        cout << c;
    return 0;
}
