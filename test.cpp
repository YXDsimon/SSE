#include <iostream>
#include <immintrin.h>
using namespace std;
#define N 5
int main()
{
    __m128 t1, t2;
    float temp[4];
    float a[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    temp[0] = temp[1] = temp[2] = temp[3] = 2;
    t2 = _mm_loadu_ps(temp);
    for (int j = 0; j < 12; j += 4)
    {
        // a[k][j] /= a[k][k];
        t1 = _mm_loadu_ps(a + j);
        t1 = _mm_div_ps(t1, t2);
        _mm_store_ps(a + j, t1);
    }
}