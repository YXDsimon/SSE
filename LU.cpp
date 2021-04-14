#include <iostream>
using namespace std;
#define N 6
void printA(float a[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}
int main()
{
    float a[N][N];
    for (int i = 0; i < N; i++) //初始化一个矩阵
    {
        for (int j = 0; j < N; j++)
        {
            a[i][j] = 2 + i + j;
        }
    }
    printA(a);
    for (int k = 0; k < N; k++)
    {
        for (int j = k + 1; j < N; j++)
        {
            a[k][j] /= a[k][k];
        }
        a[k][k] = 1.0;
        // cout << endl;
        // printA(a);
        for (int i = k + 1; i < N; i++)
        {
            for (int j = k + 1; j < N; j++)
            {
                a[i][j] -= a[i][k] * a[k][j];
            }
            cout << endl;
            printA(a);
            a[i][k] = 0;
        }
    }
    cout << endl;
    printA(a);
    return 0;
}