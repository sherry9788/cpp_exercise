#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

int main()
{
    loop:
/*
        int score;
        cin >> score;
        cout << ( ( score < 60 ) ? "fail" :
                 ( score <= 75 ) ? "low pass" :
                 ( score <= 90 ) ? "pass" : "high pass" )
                 << endl ;
*/
        int score ;
        cin >> score ;
        if ( score < 60 && score >= 0 )
            cout << "fail" << endl;
            else if ( score <= 75 && score >= 0 )
                cout << "low pass" << endl;
            else if ( score <= 90 && score >= 0 )
                cout << "pass" << endl;
            else if ( score <= 100 && score >= 0 )
                cout << "high pass" << endl;
    goto loop;
    return 0;
}
