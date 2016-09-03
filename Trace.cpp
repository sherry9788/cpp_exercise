#include <iostream>

using namespace std;

int trace(int *mat,int n)
{
    int tr = 0;
    for(int i = 0;i < n*n;i += (n+1))
        tr += mat[i];
    return tr;
}

int main()
{
    int mat[3][3] = {1,10,30,20,1,30,200,300,1};
    cout << trace((int*)mat,3) << endl;
    for (int i = 0;i < 3;++ i){
        for (int j = 0;j <3;++ j)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    return 0;
}
