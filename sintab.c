#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define LINESIZE 16
#define PCM_T unsigned short
typedef PCM_T pcm_t;

#define RESOLUTION 15
#define TABSIZE 4096
#define MAXVAL  ((pcm_t) ((1 << RESOLUTION)-1))
#define MAXHALF ((pcm_t)  (1 << (RESOLUTION-1)))

int main(void)
{
	const double pi = 4*atan(1.0);
	pcm_t sintab[TABSIZE];

	printf("#define RESOLUTION %d\n", RESOLUTION);
	printf("#define MAXVAL  ((unsigned short) ((1 << RESOLUTION)-1))\n");
	printf("#define MAXHALF ((unsigned short)  (1 << (RESOLUTION-1)))\n");
	printf("#define TABSIZE %d\n", TABSIZE);
	printf("const unsigned short sintab[TABSIZE] = {", TABSIZE);
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
	printf("\n");

	printf("const unsigned int peak[16] = {", TABSIZE);
	for (int k = 0; k < 16; k++) {
		int maxval = 0;

		for (int i = 0; i < TABSIZE-1; i++) {
			int sample = 0;

			for (int j = 0; j < 4; j++) {
				if (k & (1 << j)) sample += sintab[i*(1 << j) & (TABSIZE-1)];
			}
			if (maxval < sample) maxval = sample;
		}
		printf("%6d", maxval);
		if (k == 15) printf("};\n");
		else printf(", ");
		
	}
}