#include <iostream>
#include <string>
#include <vector>

using namespace std;

int tab[8][8],tab1[8][8];

bool hor(int (*tab)[8],int i,int j)
{
    for (int k = 0;k < 8;++ k)
        if (tab[k][j])
            return 0;
    return 1;
}

bool ver(int (*tab)[8],int i,int j)
{
    for (int k = 0;k < 8;++ k)
        if (tab[i][k])
            return 0;
    return 1;
}

bool diag(int (*tab)[8],int i,int j)
{
    for (int k = -7;k < 8;++ k)
        if ((i+k) >= 0 && (i+k) < 8 && (j+k) >= 0 && (j+k) < 8 && tab[i+k][j+k])
            return 0;
    return 1;
}

bool anti_diag(int (*tab)[8],int i,int j)
{
    for (int k = -7;k < 8;++ k)
        if ((i-k) >= 0 && (i-k) < 8 && (j+k) >= 0 && (j+k) < 8 && tab[i-k][j+k])
            return 0;
    return 1;
}

void myswap(int (*tab)[8],int (*tab1)[8])
{
    for (int i = 0;i < 8;++ i)
        for (int j = 0;j < 8;++ j)
            tab1[i][j] = tab [i][j];
}

bool comp(int (*tab)[8])
{
    int sum = 0;
    for (int i = 0;i < 8;++ i)
        for (int j = 0;j < 8;++ j)
            if (tab[i][j])
            ++ sum;
    if (sum == 8)
        return 1;
    return 0;
}

void op(int (*tab)[8],int k)
{
    tab[k][0] = 1;
    int i = 0,j = 0;
    for (i = 0;i < 8;++ i)
        for (j = 0;j < 8;++ j)
            if (hor(tab,i,j) && ver(tab,i,j) && diag(tab,i,j) &&anti_diag(tab,i,j))
                tab[i][j] = 1;

}

int main()
{
    int i = 0,j = 0;
    for (int k = 0;k < 8;++ k){
        for (i = 0;i < 8;++ i)
            for (j = 0;j < 8;++ j)
                tab[i][j] = 0;
        op(tab,k);
        if (comp(tab))
            myswap(tab,tab1);
    }
    for (i = 0;i < 8;++ i){
        for (j = 0;j < 8;++ j)
            cout << tab1[i][j] << " ";
        cout << endl;
    }
    return 0;
}
