#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<string> v;
    string word;

    while (cin >> word) {
        v.push_back(word);
        cout << v.capacity() << "\n";
    }

    return 0;
}
