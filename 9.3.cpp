#include <iostream>
#include <list>
#include <vector>
#include <deque>

using namespace std;

int main()
{
    vector<int> ivec;
    int target = 10;
    for (int i = 0;i < 10;++ i){
        int temp;
        cin >> temp;
        ivec.push_back(temp);
    }
    int p,q;
    cin >> p >> q;
    if (p > q){
        int temp = q;
        q = p;
        p = temp;
    }
    auto iter1 = ivec.begin(),iter2 = ivec.begin();
    iter1 += p;
    iter2 += q;
    bool b = 0;
    while (iter1 != iter2){
        if (*iter1 == target){
            b = 1;
            break;
        }
        ++ iter1;
    }
    cout << b << endl;
    return 0;
}
