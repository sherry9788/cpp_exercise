#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main()
{
    vector<string> svec;
    string s;
    int i(1),k(0);
    cout << "Input some words." << endl;
    while ( cin >> s )
        svec.push_back(s);
    auto vend = svec.end();
    for ( auto iter = svec.begin() ; iter != vend ; ){
        iter = iter + 1 ;
        if ( iter != vend && *iter == *( iter - 1 ) )
            ++ i ;
        else
            k = ( ( i > k ) ? i : k ) ;
    }
    cout << k << endl;
    return 0;
}
