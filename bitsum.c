#include <stdio.h>
#include <stdlib.h>

/* Set bits from least significant bit (LSB) to position (x-1) */
#define	SET_ALL_BITS(x)		(((unsigned long long)1<<((x))) - 1)

/* Number of set bits formula */
#define	COUNT_BITS(x)		((x) * (unsigned long long)1<<((x)-1))

/*
 * Sum of set bits for integer N by adding them in groups of 2^i - 1
 *
 *	For intergers of the form:  2^i - 1 such as 1, 3, 7, 15, etc.
 *
 *	00	
 *	01	i x 2^i matrix
 *	10
 *	11
 * 
 *	Consider the entire matrix of bits from [0, 2^i - 1] and note
 *	that for each bit position only half are set. So to find the
 *	number of set bits, divided the matix by by 2.
 *    
 *	(i x 2^i)
 *	---------   =   i x 2^(i-1)  number of set bits formula
 *	    2
 *    
 */
unsigned long long
bitsum(unsigned long long N)
{
	int			i;		// Bit position of MSB
	unsigned long long	ceiling;	// 2^(i+1) - 1, such that N < ceiling
	unsigned long long	floor;		// 2^i - 1, such that N > floor
	unsigned long long	limit;		// Out of bounds limit
	
	if (N == 0)
		return (0);

	/* 2^32 is too large for OS->HV->Windows */
	limit = SET_ALL_BITS(32);
	if (N > limit) {
		printf("Out of bounds: %llu > %llu\n", N, limit);
		return(0);
	}

	/* Bit position of the most significant bit (MSB) */
	i = 0;
	for (int m = N>>1; ((1<<i) - 1) < m; ++i);

	ceiling = SET_ALL_BITS(i + 1);
	floor = ceiling>>1;

	if (N == ceiling)
		return (COUNT_BITS(i + 1));

	/* Remainder, set bits of the floor, bits from MSB to floor */
	return (bitsum(N - floor) + COUNT_BITS(i) + (N - floor - 1));
}

int
main()
{
	unsigned long long	Num;

	/* Powers of 2 */
	for (int i = 0; i <= 32; ++i) {
		Num = ((unsigned long long)1<<i);
		printf("For n=%llu(2^%d), bitsum=%llu\n", Num, i, bitsum(Num));
	}
	
	/* Largest integer that can be calculated */
	Num = ((unsigned long long)1<<32) - 1;
	printf("For n=%llu(2^32-1), bitsum=%llu\n", Num, bitsum(Num));

	/* Second largest (most activation records) */
	printf("For n=%llu(2^32-2), bitsum=%llu\n", Num - 1, bitsum(Num - 1));
}
