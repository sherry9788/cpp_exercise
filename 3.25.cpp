#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

int main()
{
    vector<int> score,grade(11);
    cout<<"Input the scores"<<endl;
    int num;
    while(cin>>num)
        if(num<=100 && num>=0)
            score.push_back(num);
    auto iter1=score.begin(),iter2=grade.begin();
    for(;iter1!=score.end();iter1++){
        iter2=grade.begin()+*iter1/10;
        *iter2+=1;
    }
    for(auto c:grade)
        cout<<c<<endl;
    return 0;
}
