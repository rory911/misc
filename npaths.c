#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>

/* Just before the matrix dimensions cross beyond the number of seconds */
#define	LIMIT		18

#define	MIN(a,b)	(((a) < (b)) ? (a) : (b))
#define	MAX(a,b)	(((a) > (b)) ? (a) : (b))

/*
 * Number of paths through an M x N matrix where the only moves allowed are down and
 * right. This simple minded approach can generate a large number of activation records
 * and can be very slow for values larger than LIMIT.
 */
u_int64_t
npaths(u_int64_t M, u_int64_t N) 
{ 
	if (M == 1 || N == 1) 
		return (1); 

	/* npaths(M-1, N-1) */
	return (npaths(M-1, N) + npaths(M, N-1)); 
}

/*
 * For large M x N, there can be an inordinate number of activation records.  A better
 * solution is to consider the mathematical relationship of the number of paths through
 * a 2 dimensional matrix.  For an M x N, there must be (M - 1) moves down, plus there
 * must be (N - 1) moves right.  The total number of moves (M - 1) + (N - 1) = (M + N -2)
 * From the total number of moves "choose" (M - 1) or (N - 1).  Such a choice is known as
 * a mathematical combination, and is defined and simplified as follows:
 *
 *    C(M + N - 2, N - 1)  =      (M + N - 2)!      =  C(M + N - 2, m - 1)       [EQ 1]
 *                            -------------------
 *                            (M - 1)! * (N - 1)!
 *
 * Let m = M - 1, n = N - 1, and the from symmetry of [EQ 1], let m >= n, then
 *
 *    C(m + n, n) =  1 * 2 * .. * m * .. * (m + n)      (m!) * (m + 1) * .. * (m + n)
 *                   -----------------------------  =   ---------------------------
 *                               m! * n!                           (m!) * n!
 * 
 *    After canceling (m!) from the numerator and denominator, then
 *
 *    C(m, n) =  (m + 1) * .. * (m + n)
 *               ----------------------
 *                         n!
 * 
 *    Now, restore M and N:
 *
 *    C(M + N - 2, N - 1)  =   M * .. * (M + N - 2)                              [EQ 2]
 *                             --------------------
 *                                   (N - 1)!
 */
u_int64_t
C(u_int64_t M, u_int64_t N)
{
	long double numerator = 1, denominator = 1;

	/* numerator = M * .. * (M + N - 2) */
	for (int i = MIN(M, N); i <= M + N - 2; ++i)
		numerator *= i;

	/* denominator = (N - 1)! */
	for (int i = 1; i <= MAX(M - 1, N - 1); ++i)
		denominator *= i;

	/* [EQ 2] */
	return ((u_int64_t)(numerator / denominator));
}

/* Print the results with elapsed time */
void
tm(u_int64_t (*f)(u_int64_t, u_int64_t), u_int64_t M, u_int64_t N)
{
	clock_t bgn;
	double msec;
	u_int64_t num;

	bgn = clock();
	num = f(M, N);
	msec =  (clock() - bgn) / (double)CLOCKS_PER_SEC;
	printf("number of paths for a %lu x %lu matrix is %lu (%f sec)\n", M, N, num, msec);
}

int
main() 
{ 
	int M, N;

	printf("Enter an M x N matrix as positive integers[1-%d 1-%d]: ", LIMIT, LIMIT);
        scanf("%d %d", &M, &N);
	if (M < 1 || N < 1 || M > LIMIT || N > LIMIT) {
		printf("Out of bounds: integers must be between 1 and %d\n", LIMIT);
		exit (1);
	}

	printf("Combination: ");
	tm(&C, M, N);
	printf("  Recursion: ");
	tm(&npaths, M, N);
	exit(0);
} 
