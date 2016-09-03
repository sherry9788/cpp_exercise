#include <iostream>
#include <vector>
#include <memory>

using namespace std;

shared_ptr<vector<int> > fx(int i)
{
    shared_ptr<vector<int> > ivp = make_shared<vector<int> > () ;
    ivp -> push_back(i);
    ivp -> push_back(i);
    return ivp;
}

int main()
{
    int i;
    cin >> i;
    auto ivp = fx(i);
    for (auto c:*ivp)
        cout << c << endl;
    return 0;
}
