#include <iostream>
#include <immintrin.h>
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
    __m256 t1, t2, t3, t4, t5;
    for (int k = 0; k < N; k++)
    {
        t2 = _mm256_set1_ps(a[k][k]);
        for (int j = k + 1; j < N; j += 8)
        {
            if ((N - j) < 8)
            {
                for (j; j < N; j += 1)
                {
                    a[k][j] /= a[k][k];
                }
                break;
            }
            else
            {
                t1 = _mm256_loadu_ps(a[k] + j);
                t1 = _mm256_div_ps(t1, t2);
                _mm256_storeu_ps(a[k] + j, t1);
            }
        }
        a[k][k] = 1.0;
        for (int i = k + 1; i < N; i++)
        {
            for (int j = k + 1; j < N; j += 8)
            {
                if ((N - j) < 8)
                {
                    for (j; j < N; j += 1)
                    {
                        a[i][j] -= a[i][k] * a[k][j];
                    }
                    break;
                }
                else
                {
                    t1 = _mm256_set1_ps(a[i][k]); //这里错了
                    t2 = _mm256_loadu_ps(a[k] + j);
                    t3 = _mm256_mul_ps(t1, t2);
                    t4 = _mm256_loadu_ps(a[i] + j);
                    t5 = _mm256_sub_ps(t4, t3);
                    _mm256_storeu_ps(a[i] + j, t5);
                }
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
    //printA(a);
    return 0;
}