#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

istream& func(istream &is)
{
    string buf;
    while (is >> buf)
        cout << buf << endl;
    is.clear();
    return is;
}

int main()
{
    string s;
    getline(cin,s);
    istringstream iss(s);
    func(iss);
    return 0;
}
