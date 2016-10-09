#include <iostream>
#include <string>
#include <vector>

using namespace std;

int sum_for_int(const vector<string> &v)
{
    int sum = 0;
    for (auto const& s : v) sum += stoi(s);
    return sum;
}

float sum_for_float(const vector<string> &v)
{
    float sum = 0.0;
    for (auto const& s : v) sum += stof(s);
    return sum;
}

int main()
{
    vector<string> v = {"1", "2", "3", "4.5"};
    cout << sum_for_int(v) << endl;
    cout << sum_for_float(v) << endl;

    return 0;
}
