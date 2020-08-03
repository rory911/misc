#include <stdio.h>

#define	PRT(x)						\
							\
	printf("[");					\
	for (int i = 0; i < N; ++i)			\
		printf("%d, ", (x));			\
	printf("\b\b  \b\b]\n\n");


/*
 * Rearrange a given array so that Arr[i] becomes Arr[Arr[i]]
 * with O(1) extra space (in situ).
 *
 * Example:
 *	Input  [1, 0]
 *	Output [0, 1]
 *
 * Let N = size of the array, such that
 * 	The domain and range of the array are [0, N-1],
 *	N^2 does not overflow the signed integer type
 *
 * Complexity:
 *	O(log N) + O(2N) = O(N)
 */
void
rearrange(int Arr[], int N)
{
	int i, n, m, s;

	/* Nothing to do */
	if (N < 1) return;

	/* Calculate the bit shift */
	for (s = 0, n = N; n > 0; ++s)			// O(log N)
		n >>= 1;
		
	/* Encode [(new & bitmask) | (orig)] */
	for (i = 0, m = (1<<s) - 1; i < N; ++i)		// O(N)
		/* Arr[i] itself starts unencoded */
		Arr[i] |= (Arr[Arr[i]] & m)<<s;

	/* Decode with a simple bit shift */
	for (i = 0; i < N; ++i)				// O(N)
		Arr[i] = Arr[i]>>s;
}

int
main()
{
	int Arr[] = { 2, 7, 3, 5, 0, 6, 4, 1 };		// will not sort
	int N = sizeof(Arr) / sizeof(int); 

	printf("\n  Original: ");
	PRT(Arr[i]);

	printf("  Expected: ");
	PRT(Arr[Arr[i]]);

	rearrange(Arr, N);

	printf("Rearranged: ");
	PRT(Arr[i]);
}
