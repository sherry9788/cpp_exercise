/*
#include <cstdlib>
#include <iostream>

using namespace std;

char *mycat(char *ch1,char *ch2)
{
    size_t i = 0,j = 0;
    while (ch1[i ++]);
    while (ch2[j ++]);
    char *p;
    p = (char *)malloc(sizeof(char)*(i+j));
    for (int m = 0;m < i - 1;++ m)
        p[m]=ch1[m];
    for (int m = 0;m < j;++ m)
        p[m+i-1]=ch2[m];
    return p;
}

int main()
{
    char ch1[] = "Hello ",ch2[] = "world!";
    char *p = mycat(ch1,ch2);
    cout << p << endl;
    free(p);
    return 0;
}
*/

/*
#include <cstdlib>
#include <iostream>

using namespace std;

char *mycat(char *ch1,char *ch2)
{
    size_t i = 0,j = 0;
    while (ch1[i ++]);
    while (ch2[j ++]);
    char *p;
    p = new char [i+j];
    for (int m = 0;m < i - 1;++ m)
        p[m]=ch1[m];
    for (int m = 0;m < j;++ m)
        p[m+i-1]=ch2[m];
    return p;
}

int main()
{
    char ch1[] = "Hello ",ch2[] = "world!";
    char *p = mycat(ch1,ch2);
    cout << p << endl;
    delete [](p);
    return 0;
}
*/


#include <iostream>

using namespace std;

char *mycat(string s1,string s2)
{
    char *p = new char[s1.size() + s2.size() + 1];
    for (int i = 0;i < s1.size();++ i)
        p[i] = s1[i];
    for (int i = s1.size();i < s1.size() + s2.size();++ i)
        p[i] = s2[i - s1.size()];
    return p;
}

int main()
{
    string s1 = "Hello ",s2 = "world!";
    cout << mycat(s1,s2) << endl;
    delete [](mycat(s1,s2));
    return 0;
}


/*
#include <cstdlib>
#include <iostream>

using namespace std;

char *mycat(string s1,string s2)
{
    char *p = (char *)malloc(sizeof(char)*(s1.size() + s2.size() +1));
    for (int i = 0;i < s1.size();++ i)
        p[i] = s1[i];
    for (int i = s1.size();i < s1.size() + s2.size();++ i)
        p[i] = s2[i - s1.size()];
    return p;
}

int main()
{
    string s1 = "Hello ",s2 = "world!";
    cout << mycat(s1,s2) << endl;
    free(mycat(s1,s2));
    return 0;
}
*/
