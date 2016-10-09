#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Person;

istream &read(istream &,Person &);

struct Person
{
    string address = "UCLA";
    string name = "Sherry";
    vector<long long> lvec = {0};
    void aandn() const
    {
        cout << address << endl << name << endl;
    }
    Person() = default;
    Person(istream &is)
    {
        read(is,*this);
    }
};

istream &read(istream &is,Person &item)
{
    getline(is,item.name);
    getline(is,item.address);
    while (is){
        long long l1;
        is >> l1;
        item.lvec.push_back(l1);
    }
    return is;
}

ostream &print(ostream &os,Person &item)
{
    os << item.name << endl << item.address << endl;
    for (auto iter = item.lvec.begin();iter < item.lvec.end()-1;++ iter)
        os << *iter << endl;
    return os;
}

int main()
{
    Person p1;
    print(cout,p1);
    return 0;
}
