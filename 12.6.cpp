#include <iostream>
#include <vector>
#include <memory>

using namespace std;

vector<int> *fx(int i)
{
    vector<int> *ivp = new vector<int>;
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
    delete ivp;
    return 0;
}
