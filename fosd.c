#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef unsigned short pcm_t;

#define MAXVAL  ((pcm_t) ((1 << (sizeof(pcm_t)*8))-1))
#define MAXHALF ((pcm_t)  (1 << (sizeof(pcm_t)*8-1)))

unsigned char fosd (pcm_t pcm, int acc[1], pcm_t fdbk) 
{
	int diff;

	diff =   fdbk;
	diff +=  pcm;
	diff >>= 1;

	acc[0] += diff-MAXHALF;
	return (acc[0] > 0) ? 1 : 0;
}

unsigned char sosd (pcm_t pcm, int acc[2], pcm_t fdbk)
{
	int diff1;
	int diff2;

	diff1 =   fdbk;
	diff1 +=  pcm;
	diff1 >>= 1;

	acc[0] += diff1-MAXHALF;

	diff2  = acc[0];
	diff2 += MAXHALF;
	diff2 += fdbk;
	diff2 >>= 1;

	acc[1] += diff2;
	acc[1] -= MAXHALF;

	return (acc[1] > 0) ? 1 : 0;
}

int main(void)
{
	const double pi = 4*atan(1.0);
	pcm_t sintab[64];

	for(int i = 0; i < sizeof(sintab)/sizeof(sintab[0]); i++) {
		sintab[i] = ((1 << (sizeof(pcm_t)*8))-1)*((sin(2.0*pi*i/(sizeof(sintab)/sizeof(sintab[0])))+1.0)/2.0);
	}

	int   acc[2] = { 0, 0 };
	pcm_t fdbk = 0;
	printf("%4s %6s %6s %8s %8s %6s\n", "n", "sample", "fdbk", "acc1", "acc2", "output");
	for(int i = 0; i < sizeof(sintab)/sizeof(sintab[0]); i++) {
		unsigned char sd;
		// sd = sosd(sintab[i], acc, fdbk);
		sd = fosd(sintab[i], acc, fdbk);
		printf("%4u %6hu %6hu %8d %8d %6d\n", i, sintab[i], fdbk, acc[0], acc[1], sd);
		fdbk = (sd > 0) ? 0 : MAXVAL;
	}
}