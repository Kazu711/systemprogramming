#if 0

f(x)  =-(x-1)^2 + 1

#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>


enum { N=1000000000L, };

int main(void)
{
    double x,s,d_x,fx;
    long long n;

    d_x = (double)2.0 / N;

    s=0.0;
#pragma omp parallel for reduction (+:s)
    for(n=1;n<N+1;n++){
        x = (double) n/N;
        fx = 1.0 - ((x-1.0)*(x-1.0));
        s += fx * d_x;
    }
    printf("s= %25.15lf\n", s);
    return 0;
}
