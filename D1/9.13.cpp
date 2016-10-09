#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

int main()
{
    list<int> ilst(5, 4);
    vector<int> ivc(5, 5);
    vector<double> dvc(ilst.begin(), ilst.end());
    for (auto i : ilst)
        cout << i;
    cout << endl;
    for (auto t : dvc)
        cout << t;
    cout << endl;
    vector<double> dvc2(ivc.begin(), ivc.end());
    for (auto i : ivc)
        cout << i;
    cout << endl;
    for (auto t : dvc2)
        cout << t;
    return 0;
}
