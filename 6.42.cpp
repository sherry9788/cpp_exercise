#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

char *make_plural(string &s,const string &str = "s")
{
    s += str;
    return &s[0];
}

int main()
{
    string w1 = "success",w2 = "failure";
    char *p = 0;
    p = make_plural(w1,"es");
    for (;*p;++ p)
        cout << *p;
    cout << endl;
    p = make_plural(w2);
    for (;*p;++ p)
        cout << *p;
    cout << endl;
}
