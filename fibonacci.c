#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Just under 1 minute of recursion, and the 1 sec mark is crossed at 41
 */
#define	LIMIT		48


/* Recursive Fibonacci */
static long
rFibonacci(int n)
{
	if (n < 2)
		return ((long) n);

	return (rFibonacci(n-1) + rFibonacci(n-2));
}

/* Iterative Fibonacci */
static long
iFibonacci(int n)
{
	int	i;
	long	f[n];

	if (n < 2)
		return ((long) n);

	for (f[0] = 0, f[1] = 1, i = 2; i <= n; ++i)
		f[i] = f[i-1] + f[i-2];

	return (f[n]);
}

/* Print the results with elapsed time */
void
tm(long (*f)(int), int N)
{
        clock_t bgn;
        double msec;
        long num;

        bgn = clock();
        num = f(N);
        msec =  (clock() - bgn) / (double)CLOCKS_PER_SEC;
        printf("Fibonacci(%d) = %ld (%f sec)\n", N, num, msec);
}

int
main()
{
	int	n = 0;

	printf("Input a positive integer[0-%d]: ", LIMIT);
	scanf("%d", &n);
	if (n < 0 || n > LIMIT) {
		printf("Error: '%d' is out of bounds\n", n);
		exit(1);
	}

	printf("Iteration: ");
	tm(&iFibonacci, n);
	printf("Recursion: ");
	tm(&rFibonacci, n);
	exit(0);
}
