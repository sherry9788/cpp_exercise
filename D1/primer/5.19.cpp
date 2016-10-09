#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main()
{
    do{
        cout << "Input two strings." << endl;
        string s1,s2;
        cin >> s1 >> s2;
        cout << ( ( s1.size() > s2.size() ) ? s2 : s1 );
        cout << endl;
    } while (cin);
    return 0;
}
