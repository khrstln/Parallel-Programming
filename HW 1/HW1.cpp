#include <iostream>
#include <cmath>
#include <xmmintrin.h>

void normal(float* a, float* b, int N)
{
    for (int i = 0; i < N; i++)
    {
        b[i] = sqrt(a[i]);
    }
}

void sse(float* a, float* b, int N)
{   
    int remainder = N % 4;
    int newSize = N - remainder;

    for (int i = 0; i < N; i+=4)
    {
        __m128 xmm0 = _mm_load_ps(&a[i]);
        xmm0 = _mm_sqrt_ps(xmm0);
        _mm_store_ps(&b[i], xmm0);
    }
    
    for (int i = newSize; i < N; ++i) {
        b[i] = std::sqrt(a[i]);
    }

}



int main()
{
    int N = 10;
    float a[N];
    for (int i = 0; i < N; i++)
    {
        a[i] = i*i;
    }

    float res_normal[N];

    normal(a, res_normal, N);

    std::cout << "Normal square root:" << std::endl;
    for (int i = 0; i < N; i++)
    {
        std::cout << res_normal[i] << " ";
    }
    std::cout << std::endl;

    float res_sse[N]; 

    sse(a, res_sse, N);

    std::cout << "SSE square root:" << std::endl;
    for (int i = 0; i < N; i++)
    {
        std::cout << res_sse[i] << " ";
    }

    return 0;
}