#include <iostream>
using namespace std;
#define N 2000
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
void LU(float **a)
{
    for (int k = 0; k < N; k++)
    {
        for (int j = k + 1; j < N; j++)
        {
            a[k][j] /= a[k][k];
        }
        a[k][k] = 1.0;
        for (int i = k + 1; i < N; i++)
        {
            for (int j = k + 1; j < N; j++)
            {
                a[i][j] -= a[i][k] * a[k][j];
            }
            a[i][k] = 0;
        }
    }
}
int main()
{
    float **a = new float *[N];
    for (int i = 0; i < N; i++) //初始化一个矩阵
    {
        a[i] = new float[N];
        for (int j = 0; j < N; j++)
        {
            a[i][j] = 2 + j + i;
        }
    }
    LU(a);
    // printA(a);
    // printA(a);
    return 0;
}