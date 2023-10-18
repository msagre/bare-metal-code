#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PCM_T unsigned short
typedef PCM_T pcm_t;

#define TABSIZE 4096
#define MAXVAL  ((pcm_t) ((1 << (sizeof(pcm_t)*8))-1))
#define MAXHALF ((pcm_t)  (1 << (sizeof(pcm_t)*8-1)))
#define LINESIZE 16

int main(void)
{
	const double pi = 4*atan(1.0);
	pcm_t sintab[TABSIZE];

	printf("#define TABSIZE %d\n", TABSIZE);
	printf("unsigned short sintab[TABSIZE] = {", TABSIZE);
	int j = 0;
	for(int i = 0; i < TABSIZE; i++) {
		sintab[i] = (MAXVAL/2)*sin(2.0*pi*i/TABSIZE)+MAXHALF;
		if (j == 0) {
			printf("\n\t");
		}
		if (i == TABSIZE-1) {
			printf("%5d};", sintab[i]);
		} else {
			printf("%5d, ", sintab[i]);
		}
		j += 1;
		j %= LINESIZE;
	}
}