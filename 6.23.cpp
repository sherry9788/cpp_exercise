#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

void print(int i)
{
    cout << i << endl;
}

void print(vector<int> vec)
{
    for (auto iter = vec.begin();iter != vec.end();++ iter)
        cout << *iter << " ";
    cout << endl;
}

void print(const string &s)
{
    for (auto iter = s.begin();iter != s.end();++ iter)
        cout << *iter;
    cout << endl;
}

void print(int *i,size_t n)
{
    for (size_t m = 0;m != n;++ i,++ m)
        cout << i << " ";
    cout << endl;
}

void print(int (*p1)[4])
{
    for (int n1 = 0;n1 != 4;++ n1,++ p1){
        int *p2 = *p1;
        for (int n2 = 0;n2 != 4;++ n2,++ p2)
            cout << *p2 << " ";
        cout << endl;
    }
}

int main()
{
    cout << "Input a number:" << endl;
    int i1;
    cin >> i1;
    print(i1);
    system("pause");
    cout << "Input a vector<int>:" << endl;
    vector<int> i2;
    while (cin >> i1)
        i2.push_back(i1);
    print(i2);
    cin.clear();
    system("pause");
    cout << "Input a string:" << endl;
    string i3;
    getline(cin,i3);
    print(i3);
    system("pause");
    cout << "Input a matrix(4X4):" << endl;
    int i4[4][4];
    for (int j1 = 0;j1 != 4;++ j1)
        for (int j2 = 0;j2 != 4;++ j2)
        cin >> i4[j1][j2];
    print (i4);
    return 0;
}
