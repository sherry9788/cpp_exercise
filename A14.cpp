#include <iostream>
#include <string>

using namespace std;

int main()
{
    loop:
    struct date{
    int year;
    int month;
    int day;
    };
    int mon[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    date d1;
    cin >> d1.year >> d1.month >> d1.day;
    int seq = 0;
    seq += d1.day;
    for (int i = d1.month;i > 0;i --)
        seq += mon[i];
    if ((d1.year % 4 == 0 && d1.year % 100 != 0 || d1.year % 400 == 0) && d1.month > 2)
        seq += 1;
    cout << seq << endl;
    goto loop;
    return 0;
}
