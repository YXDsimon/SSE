#include <iostream>
#include <immintrin.h>
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
            a[i][j] = 2 + j + i;
        }
    }
    printA(a);
    __m128 t1, t2, t3, t4, t5;
    for (int k = 0; k < N; k++)
    {
        float temp[4];
        temp[0] = temp[1] = temp[2] = temp[3] = a[k][k];
        t2 = _mm_loadu_ps(temp);
        for (int j = k + 1; j < N; j += 4)
        {
            // a[k][j] /= a[k][k];
            t1 = _mm_loadu_ps(a[k] + j);
            t1 = _mm_div_ps(t1, t2);
            _mm_storeu_ps(a[k] + j, t1);
        }
        a[k][k] = 1.0;
        cout << endl;
        printA(a);
        for (int i = k + 1; i < N; i++)
        {
            for (int j = k + 1; j < N; j += 4)
            {
                t1 = _mm_loadu_ps(a[i] + k);
                t2 = _mm_loadu_ps(a[k] + j);
                t3 = _mm_mul_ps(t1, t2);
                t4 = _mm_loadu_ps(a[i] + j);
                t5 = _mm_sub_ps(t4, t3);
                _mm_storeu_ps(a[i] + j, t5);
                //a[i][j] -= a[i][k] * a[k][j];
            }

            a[i][k] = 0;
        }
    }
    cout << endl;
    printA(a);
    return 0;
}