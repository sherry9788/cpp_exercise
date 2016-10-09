#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main()
{
    vector<int> ivec1,ivec2,ivec3;
    int i1,i2;
    cout << "Input some numbers to i1." << endl;
    while (cin >> i1)
        ivec1.push_back(i1);
    system("pause");
    cin.clear();
    cout << "Input some numbers to i2." << endl;
    while (cin >> i2)
        ivec2.push_back(i2);
    ivec3 = ivec1;
    ivec1 = ivec2.size() > ivec1.size() ? ivec1 : ivec2;
    ivec2 = ivec2.size() > ivec3.size() ? ivec2 : ivec3;
    auto vend = ivec1.end();
    for (auto iter1 = ivec1.begin() , iter2 = ivec2.begin() ; iter1 != vend && (*iter1) == (*iter2) ; ++ iter1 , ++ iter2)
        if (iter1 + 1 == vend)
            cout << "Yes" <<endl;
    return 0;
}
