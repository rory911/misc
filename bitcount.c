#include <stdio.h>
#include <stdlib.h>

#define	BYTE	8
#define	ZERO	48
#define	ONE	49
#define	FIRST	1<<(BYTE - 1)
#define LAST	1<<BYTE

/* Number of bits set for a given positive integer N */
unsigned int
bitcount(unsigned int N)
{
	unsigned int total = 0;

	while (N) { 
		N &= (N - 1); 	// memories from my days at Bell Labs
		total++; 
	} 

	return (total);
}

/* Simple minded integer to binary unicode */
char *
i2bin(unsigned int N)
{
	char *bin = (char *)calloc(BYTE, sizeof(char));

	for (int i = BYTE - 1; i >= 0; --i) {
		bin[i] = (N & 1) ? ONE : ZERO;
		N >>= 1;
	}
	return (bin);
}

int
main()
{
	char *bits;

	for (unsigned int i = FIRST; i < LAST; ++i) {
		bits = i2bin(i);
		printf("%3d(%s), bits=%u\n", i, bits, bitcount(i));
		free(bits);
	}
}
