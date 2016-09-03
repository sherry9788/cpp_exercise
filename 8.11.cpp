#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct info
{
    string name;
    vector<string> phones;
    void print()
    {
        cout << name << ":" << endl;
        for (auto c:phones)
            cout << c << endl;
        cout << endl;
    }
};

int main()
{
    fstream fs("sherry.txt");
    string line,word;
    vector<info> people;
    istringstream iss;
    while (getline(fs,line)){
        info pn;
        iss.str(line);
        iss >> pn.name;
        while (iss >> word)
            pn.phones.push_back(word);
        people.push_back(pn);
        iss.clear();
    }
    for (auto c:people)
        c.print();
    return 0;
}
