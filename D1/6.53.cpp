#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cassert>

using namespace std;

int calc(int&, int&);
int calc(const int&,const int&);

int calc(char*, char*);
int calc(const char*,const char*);

int calc(char*, char*);
int calc(char* const,char* const);

int main()
{
    return 0;
}
