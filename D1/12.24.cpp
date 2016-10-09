#include <iostream>

using namespace std;

int main()
{
    string s;
    cin >> s;
    char* cp = new char[s.size()+1];
    for (int i=0; i< s.size(); ++i)
        cp[i] = s[i];
    cp[s.size()] = '\0';
    cout << cp << endl;
    delete [] cp;
}
