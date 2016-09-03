#include <iostream>
#include <list>
#include <vector>
#include <deque>

using namespace std;

int main()
{
    vector<int> vec1;    // 0
    vector<int> vec2(10);    // 0
    vector<int> vec3(10,1);  // 1
    vector<int> vec4{1,2,3,4,5}; // 1,2,3,4,5
    vector<int> vec5(vec1); // same as other_vec
    vector<int> vec6(vec5.begin(), vec5.end()); // same as other_vec
    return 0;
}
