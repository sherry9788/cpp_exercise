#include <iostream>
#include <cstdlib>

using namespace std;

bool myupper(const string &s)
{
    for(auto iter = s.begin();iter != s.end();++ iter)
        if (isupper(*iter))
        return 1;
    return 0;
}

void mytolower(string &s)
{
    for(auto iter = s.begin();iter != s.end();++ iter)
        *iter = tolower(*iter);
}

int main()
{
    loop:
    string s;
    getline(cin,s);
    cout << myupper(s) << endl;
    system("pause");
    mytolower(s);
    cout << s << endl;
    goto loop;
    return 0;
}
