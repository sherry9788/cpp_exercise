#include <iostream>
#include <forward_list>

using namespace std;

int main()
{
    forward_list<int> flst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto prev = flst.before_begin(), curr = flst.begin();
         curr != flst.end();)
        if (*curr & 0x1)
            curr = flst.erase_after(prev);
        else
            prev = curr++;

    for (auto i : flst) cout << i << " ";
    cout << endl;
}
