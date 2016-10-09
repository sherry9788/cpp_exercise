#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    map<string, vector<int>> m;
    m = {{"Alan",
          {
              1, 2, 3, 4, 5,
          }},
         {"John", {1, 5, 6, 7, 8}}};

    map<string, vector<int>>::iterator it;

    it = m.find("Alan");

    return 0;
}
