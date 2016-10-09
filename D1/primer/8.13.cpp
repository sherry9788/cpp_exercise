#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    fstream fs("sherry.txt");
    vector<string> svec;
    string s;
    while (getline(fs,s))
        svec.push_back(s);
    for (auto &c:svec){
        istringstream iss(c);
        string word;
        while (iss >> word)
            cout << word << endl;
    }
    return 0;
}
