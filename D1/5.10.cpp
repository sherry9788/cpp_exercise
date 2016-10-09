#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main()
{
    char ch;
    int aCnt = 0,eCnt = 0,iCnt = 0,oCnt = 0,uCnt = 0;
    while (cin >> ch){
        switch (ch){
            case 'a':
            case 'A':
                ++aCnt;
                break;
            case 'e':
            case 'E':
                ++eCnt;
                break;
            case 'i':
            case 'I':
                ++iCnt;
                break;
            case 'o':
            case 'O':
                ++oCnt;
                break;
            case 'u':
            case 'U':
                ++uCnt;
                break;
        }
    }
    cout << "There is " << aCnt << " \"a\" in the text"<<endl;
    cout << "There is " << eCnt << " \"e\" in the text"<<endl;
    cout << "There is " << iCnt << " \"i\" in the text"<<endl;
    cout << "There is " << oCnt << " \"o\" in the text"<<endl;
    cout << "There is " << uCnt << " \"u\" in the text"<<endl;
    return 0;
}
