#include <iostream>
#include <string>

using namespace std;

bool hor(int (*b)[5],int i,int j)
{
    for (int m = 0;m < 5;++ m)
        if (b[m][j] < b[i][j])
        return 0;
    return 1;
}

bool ere(int (*b)[5],int i,int j)
{
    for (int m = 0;m < 5;++ m)
        if (b[i][m] > b[i][j])
        return 0;
    return 1;
}

int main()
{
    int mat[5][5];
    for (int i = 0;i < 5;++ i)
        for (int j = 0;j < 5;++ j)
        cin >> mat[i][j];
    for (int i = 0;i < 5;++ i)
        for (int j = 0;j < 5;++ j)
        if (hor(mat,i,j) && ere(mat,i,j))
            cout << "(" << i+1 << "," << j+1 << ") : " << mat[i][j] << endl;
    return 0;
}
