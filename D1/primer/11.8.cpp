#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<string> exclude = {"aa", "bb", "cc"};
    for (string word; cin >> word;) {
        if (find(exclude.begin(), exclude.end(), word) != exclude.end())
            cout << "excluded!" << endl;
        else
            exclude.push_back(word);
    }
    for (auto const& s : exclude) cout << s << " ";
    cout << endl;
}
