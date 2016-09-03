#include <iostream>
#include <string>

using namespace std;

int main()
{
    loop:
    char m[10];
    cin >> m;
    double i1 = 0,i2 = 0;
    i1 = (m[0] - 48)*10 + m[1] - 48;
    i2 = (m[3] - 48)*10 + m[4] - 48;
    switch (m[2]){
        case '+':{
        cout << i1 + i2 << endl;
        break;
        }
        case '-':{
        cout << i1 - i2 << endl;
        break;
        }
        case '*':{
        cout << i1 * i2 << endl;
        break;
        }
        case '/':{
        int j = (i1 / i2) * 100;
        cout << (double) j/100 << endl;
        break;
        }
        default:
        cout << "Illigal" << endl;
    }
    goto loop;
    return 0;
}
