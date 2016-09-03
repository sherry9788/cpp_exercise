#include <iostream>
#include <string>

using namespace std;

struct date{
    int year;
    int month;
    int day;
    };

int myadd(date d1)
{
    int sum = 0;
    for (int j = d1.year - 1;j >= 2000;j --)
        if (j % 4 == 0 && j % 100 != 0 || j % 400 == 0)
            sum += 366;
        else
            sum += 365;
    return sum;
}

int myminus(date d1)
{
    int sum = 0;
    for (int j = d1.year;j != 2000;j ++)
        if (j % 4 == 0 && j % 100 != 0 || j % 400 == 0)
            sum += 366;
        else
            sum += 365;
    return sum;
}

int main()
{
    loop:
    int mon[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    date d1;
    cin >> d1.year >> d1.month >> d1.day;
    int seq = 0;
    seq += d1.day;
    for (int i = d1.month - 1;i > 0;i --)
        seq += mon[i];
    if ((d1.year % 4 == 0 && d1.year % 100 != 0 || d1.year % 400 == 0) && d1.month > 2)
        seq += 1;
    if (d1.year > 2000)
        seq += myadd(d1);
    if (d1.year < 2000)
        seq -= myminus(d1);
    seq += 700005;
    cout << seq % 7 << endl;
    return 0;
}
