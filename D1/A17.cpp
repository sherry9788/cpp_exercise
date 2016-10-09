#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string s1,s2,s3,s4,s5,s6,s7,s8,s9,temp;
    cin >> s1 >> s2 >> s3 >> s4 >> s5 >> s6 >> s7 >> s8 >> s9;
    vector<string> svec = {s1,s2,s3,s4,s5,s6,s7,s8,s9};
    auto send = svec.end();
    for (auto iter = svec.begin();iter != send;++ iter){
        auto iter1 = iter;
        auto iter2 = iter;
        for (;iter1 != send;++ iter1)
            iter2 = *iter1 < *iter2 ? iter1:iter2;
        temp = *iter2;
        *iter2 = *iter;
        *iter = temp;
    }
    for (auto c:svec)
        cout << c << endl;
    return 0;
}
