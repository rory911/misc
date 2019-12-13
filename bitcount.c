#include <stdio.h>
#include <stdlib.h>

#define	BYTE	8
#define	FIRST	1<<(BYTE - 1)
#define LAST	1<<BYTE

/* Number of bits set for a given positive integer N */
static unsigned int
bitcount(unsigned int N)
{
	unsigned int total = 0;

	while (N) { 
		N &= (N - 1); 	// memories from my days at Bell Labs
		total++; 
	} 

	return (total);
}

/* Integer to binary unicode to beautify output.  Caller must free heap memory */
static char *
i2bin(unsigned int N)
{
	char *bin = (char *)calloc(BYTE, sizeof(char));

	for (int i = BYTE - 1; i >= 0; --i) {
		bin[i] = (N & 1) ? '1' : '0';
		N >>= 1;
	}

	return (bin);
}

int
main()
{
	char *bits;

	for (unsigned int i = FIRST; i < LAST; ++i) {
		printf("%3d(%s), bitcount=%d\n", i, (bits = i2bin(i)), bitcount(i));
		free(bits);
	}
}
