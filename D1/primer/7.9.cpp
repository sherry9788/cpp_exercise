#include <iostream>
#include <vector>
#include <string>

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

istream &read(istream &is,Person &item)
{
    getline(is,item.address);
    getline(is,item.name);
    while (is){
        long l1;
        is >> l1;
        item.lvec.push_back(l1);
    }
    return is;
}

ostream &print(ostream &os,Person &item)
{
    os << item.name << endl << item.address << endl;
    for (auto c:item.lvec)
        os << c << endl;
    return os;
}

int main()
{
    Person p1;
    read(cin,p1);
    print(cout,p1);
    return 0;
}
