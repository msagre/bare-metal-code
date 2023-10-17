#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef unsigned short pcm_t;
const pcm_t half = (1 << (sizeof(pcm_t)*8-1));

void fosd (bool *sd, pcm_t *pcm, int n)
{
    int acc;
    pcm_t out;

    acc = 0;
    out = 0;
    printf("%4s %6s %6s %6s %8s %6s\n", "n", "sample", "fdbk", "diff", "acc", "output");
    for (int i = 0; i < n; i++) {
        int diff;

        diff =   out;
        diff +=  pcm[i];
        diff >>= 1;

        acc += diff-half;
        sd[i] = (out > 0) ? 0 : 1;
        printf("%4u %6hu %6hu %6d %8d %6d\n", i, pcm[i], out, diff, acc, sd[i]);
        out = (acc > 0) ? 0 : (1 << (8*sizeof(pcm_t)))-1; 
    }
}

void sosd (bool *sd, pcm_t *pcm, int n)
{

    int acc1;
    int acc2;
    pcm_t out;

    acc1 = 0;
    acc2 = 0;
    out  = 0;
    printf("%4s %6s %6s %6s %8s %6s %8s %6s\n", "n", "sample", "fdbk", "diff1", "acc1", "diff2", "acc2", "output");
    for (int i = 0; i < n; i++) {
        int diff1;
        int diff2;

        diff1 =   out;
        diff1 +=  pcm[i];
        diff1 >>= 1;

        acc1  += diff1-half;
        diff2 += (acc1+half+out)/2;
        acc2  += (diff2-half)/2;
        sd[i] = (out > 0) ? 0 : 1;
        // printf("%4u %6hu %6hu %6d %8d %6d\n", i, pcm[i], out, diff, acc, sd[i]);
        out = (acc2 > 0) ? 0 : (1 << (8*sizeof(pcm_t)))-1; 
    }
}

int main(void)
{
    const double pi = 4*atan(1.0);
    pcm_t sintab[128];
    bool sd[sizeof(sintab)/sizeof(sintab[0])];

    for(int i = 0; i < sizeof(sintab)/sizeof(sintab[0]); i++) {
        sintab[i] = ((1 << (sizeof(pcm_t)*8))-1)*((sin(2.0*pi*i/(sizeof(sintab)/sizeof(sintab[0])))+1.0)/2.0);
    }

    fosd(sd, sintab, sizeof(sintab)/sizeof(sintab[0]));
    for(int i = 0; i < sizeof(sintab)/sizeof(sintab[0]); i++) {
        printf("%4d\n", sd[i]);
    }
}