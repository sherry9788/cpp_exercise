#include <iostream>
#include <vector>

using namespace std;

struct Person
{
    string address;
    string name;
    vector<long> lvec;
    void aandn() const
    {
        cout << address << endl << name << endl;
    }
};

int main()
{
    return 0;
}
